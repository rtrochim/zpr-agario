// An extraordinarily simple test which presents a web page with some buttons.
// Clicking on the numbered button increments the number, which is visible to
// other connected clients.  WebSockets are used to do this: by the rather
// suspicious means of sending raw JavaScript commands to be executed on other
// clients.

#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"
#include "seasocks/StringUtil.h"
#include "seasocks/WebSocket.h"
#include "seasocks/util/Json.h"
#include "seasocks/PageHandler.h"

#include <cstring>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <zconf.h>
#include <cmath>
#include <map>
#include "lib/json.hpp"
#include "lib/sqlite_modern_cpp.h"
#include "Blob.h"

using namespace seasocks;
using json = nlohmann::json;
using database = sqlite::database;

class BasicHandler : public WebSocket::Handler {
public:
    explicit BasicHandler(Server* server, database &db)
            : _server(server), _db(db){}

    void onConnect(WebSocket* connection) override {
        _connections.insert(connection);
        std::cout << "Connected: " << connection->getRequestUri()
                  << " : " << formatAddress(connection->getRemoteAddress())
                  << "\nCredentials: " << *(connection->credentials()) << "\n";
    }

    void onData(WebSocket* connection, const char* data) override {
        auto payload= json::parse(data);
        json response;
        if(payload["messageType"] == "login"){
            _db << "insert into 'players' (socketId, name, active) values (?,?,?);"
               << std::string(payload["id"])
               << std::string("testname")
               << 1;
            _scores[payload["id"]] = 0;
            _blobs.push_back(*(new Blob(std::string(payload["id"]), std::string(payload["x"]), std::string(payload["y"]), std::string(payload["r"]))));
            response["messageType"] = "loggedIn";
            if (_gameBlobs.empty()) {
                int width = std::stoi(payload["width"].dump());
                int height = std::stoi(payload["height"].dump());
                for (int i = 0; i < 500; i++) {
                    std::string posX = std::to_string(-width + (std::rand() % (2*width + 1)));
                    std::string posY = std::to_string(-height + (std::rand() % (2*height + 1)));
                    _gameBlobs.push_back(*(new Blob(std::to_string(i), posX, posY, "4")));
                }
            }
            for(auto &gameBlob : _gameBlobs){
                response["gameBlobs"].push_back({{"id",gameBlob.getId()},{"x", gameBlob.getX()},{"y", gameBlob.getY()},{"r", gameBlob.getRadius()}});
            }
            connection->send(response.dump());
        } else if (payload["messageType"] == "gameBlobEat") {
            int gameBlobId = payload["gameBlobId"];
            std::string blobId = payload["blobId"];
            _scores[payload["blobId"]] += 1;
            _gameBlobs.erase(_gameBlobs.begin() + gameBlobId);
            for(auto &blob : _blobs) {
                response["blobs"].push_back({{"id", blob.getId()}, {"x", blob.getX()}, {"y", blob.getY()},{"r", blob.getRadius()}});
            }
            for(auto &gameBlob : _gameBlobs){
                response["gameBlobs"].push_back({{"id",gameBlob.getId()},{"x", gameBlob.getX()},{"y", gameBlob.getY()},{"r", gameBlob.getRadius()}});
            }
            response["messageType"] = "updateBlobs";
            response["score"] = _scores[payload["id"]];
            connection->send(response.dump());
        } else if (payload["messageType"] == "update") {
            for(auto &blob : _blobs) {
                if(blob.getId() == payload["id"]){
                    blob.setX(std::string(payload["x"]));
                    blob.setY(std::string(payload["y"]));
                    blob.setRadius(std::string(payload["r"]));
                }
                response["blobs"].push_back({{"id", blob.getId()}, {"x", blob.getX()}, {"y", blob.getY()},{"r", blob.getRadius()}});
            }
            for(auto &gameBlob : _gameBlobs){
                response["gameBlobs"].push_back({{"id",gameBlob.getId()},{"x", gameBlob.getX()},{"y", gameBlob.getY()},{"r", gameBlob.getRadius()}});
            }
            response["messageType"] = "updateBlobs";
            response["score"] = _scores[payload["id"]];
            connection->send(response.dump());
        } else if(payload["messageType"] == "logout") {
            std::string socketId = payload["id"];
            int highscore;
            _db << "select highscore from players where socketId = ?" << socketId >> highscore;
            if(highscore < _scores[payload["id"]]){
                _db << "update players set highscore = ?, active = 0 where socketId = ?" << _scores[payload["id"]] << socketId;
            }
        } else if (payload["messageType"] == "userBlobEat") {
            std::string userBlobId = payload["userBlobId"];
            auto it = std::remove_if(_blobs.begin(), _blobs.end(), [&userBlobId](Blob& obj) { return obj.getId() == userBlobId; });
            std::string eatenRadius = _blobs[it - _blobs.begin()].getRadius();
            _scores[payload["id"]] += static_cast<int>(std::atof(eatenRadius.c_str()));
            _blobs.erase(it, _blobs.end());
            for(auto &blob : _blobs) {
                response["blobs"].push_back({{"id", blob.getId()}, {"x", blob.getX()}, {"y", blob.getY()},{"r", blob.getRadius()}});
            }
            for(auto &gameBlob : _gameBlobs){
                response["gameBlobs"].push_back({{"id",gameBlob.getId()},{"x", gameBlob.getX()},{"y", gameBlob.getY()},{"r", gameBlob.getRadius()}});
            }
            response["messageType"] = "updateBlobs";
            response["score"] = _scores[payload["id"]];
            connection->send(response.dump());
        }
    }

    void onDisconnect(WebSocket* connection) override {
        _connections.erase(connection);
        std::cout << "Disconnected: " << connection->getRequestUri()
                  << " : " << formatAddress(connection->getRemoteAddress()) << "\n";
    }

private:
    std::set<WebSocket*> _connections;
    Server* _server;
    database _db;
    std::vector<Blob> _blobs;
    std::vector<Blob> _gameBlobs;
    std::map<std::string, int> _scores;
};

int main(int /*argc*/, const char* /*argv*/[]) {

    database db("../../../../agario.db");



    auto logger = std::make_shared<PrintfLogger>(Logger::Level::Debug);
    Server server(logger);

    auto handler = std::make_shared<BasicHandler>(&server, db);
    server.addWebSocketHandler("/", handler);

    try {
        server.serve("src/agario", 3000);
    }
    catch (sqlite::sqlite_exception& e) {
        std::cerr  << e.get_code() << ": " << e.what() << " during "
                   << e.get_sql() << std::endl;
    }

    return 0;
}
