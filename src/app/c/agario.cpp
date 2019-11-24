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

#include <cstring>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>

using namespace seasocks;

class MyHandler : public WebSocket::Handler {
public:
    explicit MyHandler(Server* server)
            : _server(server), _currentValue(0) {
        setValue(1);
    }

    void onConnect(WebSocket* connection) override {
        _connections.insert(connection);
        connection->send(_currentSetValue.c_str());
        std::cout << "Connected: " << connection->getRequestUri()
                  << " : " << formatAddress(connection->getRemoteAddress())
                  << "\nCredentials: " << *(connection->credentials()) << "\n";
    }

    void onData(WebSocket* connection, const char* data) override {
        if (0 == strcmp("die", data)) {
            _server->terminate();
            return;
        }
        if (0 == strcmp("close", data)) {
            std::cout << "Closing..\n";
            connection->close();
            std::cout << "Closed.\n";
            return;
        }

        const int value = std::stoi(data) + 1;
        if (value > _currentValue) {
            setValue(value);
            for (auto c : _connections) {
                c->send(_currentSetValue.c_str());
            }
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
    int _currentValue;
    std::string _currentSetValue;

    void setValue(int value) {
        _currentValue = value;
        _currentSetValue = makeExecString("set", _currentValue);
    }
};

int main(int /*argc*/, const char* /*argv*/[]) {
    auto logger = std::make_shared<PrintfLogger>(Logger::Level::Debug);

    Server server(logger);

    auto handler = std::make_shared<MyHandler>(&server);
    server.addWebSocketHandler("/ws", handler);
    server.serve("src/agario", 9090);
    return 0;
}
