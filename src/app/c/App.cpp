#include "App.h"

App::App(Server *server, Game &game): _server(server), _game(game) {}

void App::onConnect(WebSocket* connection) {
    _connections.insert(connection);
    std::cout << "Connected: " << connection->getRequestUri() << std::endl;
}

void App::onData(WebSocket* connection, const char* data) {
    auto payload= json::parse(data);
    json response;
    if(payload["messageType"] == "login"){
        _game.login(payload, response);
        connection->send(response.dump());
    } else if (payload["messageType"] == "eatGameBlob") {
        _game.eatGameBlob(payload, response);
        connection->send(response.dump());
    } else if (payload["messageType"] == "update") {
        _game.update(payload, response);
        connection->send(response.dump());
    } else if (payload["messageType"] == "eatUserBlob") {
        _game.eatUserBlob(payload, response);
        connection->send(response.dump());
    } else if(payload["messageType"] == "logout") {
        _game.logout(payload);
    }
}

void App::onDisconnect(WebSocket* connection) {
    _connections.erase(connection);
    std::cout << "Disconnected: " << connection->getRequestUri() << std::endl;
}

