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

#include "lib/json.hpp"
#include "lib/sqlite_modern_cpp.h"

using namespace seasocks;
using json = nlohmann::json;
using database = sqlite::database;

class BasicHandler : public WebSocket::Handler {
public:
    explicit BasicHandler(Server* server, database &db)
            : _server(server), _db(db){}

    void onConnect(WebSocket* connection) override {
        _connections.insert(connection);
        connection->send("WebSocket connected");
        std::cout << "Connected: " << connection->getRequestUri()
                  << " : " << formatAddress(connection->getRemoteAddress())
                  << "\nCredentials: " << *(connection->credentials()) << "\n";
    }

    void onData(WebSocket* connection, const char* data) override {
        auto json = json::parse(data);
        if(json["messageType"] == "login"){
            _db << "insert into 'players' (socketId, name, active) values (?,?,?);"
               << std::string(json["socketId"])
               << std::string(json["name"])
               << 1;

        } else if (json["messageType"] == "update"){

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
