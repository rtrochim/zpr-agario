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
#include <sqlite3.h>

using namespace seasocks;

class MyHandler : public WebSocket::Handler {
public:
    explicit MyHandler(Server* server)
            : _server(server){}

    void onConnect(WebSocket* connection) override {
        _connections.insert(connection);
        connection->send("Hello there");
        std::cout << "Connected: " << connection->getRequestUri()
                  << " : " << formatAddress(connection->getRemoteAddress())
                  << "\nCredentials: " << *(connection->credentials()) << "\n";
    }

    void onData(WebSocket* connection, const char* data) override {
        printf("===============GOT DATA:%s", data);
    }

    void onDisconnect(WebSocket* connection) override {
        _connections.erase(connection);
        std::cout << "Disconnected: " << connection->getRequestUri()
                  << " : " << formatAddress(connection->getRemoteAddress()) << "\n";
    }

private:
    std::set<WebSocket*> _connections;
    Server* _server;
};

int main(int /*argc*/, const char* /*argv*/[]) {

    sqlite3 *db;
    if(sqlite3_open("../../../../agario.db", &db)){
        printf("Cannot open database: %s", sqlite3_errmsg(db));
    }

    auto logger = std::make_shared<PrintfLogger>(Logger::Level::Debug);
    Server server(logger);

    auto handler = std::make_shared<MyHandler>(&server);
    server.addWebSocketHandler("/ws", handler);
    server.serve("src/agario", 3000);
    sqlite3_close(db);
    return 0;
}
