#ifndef ZPR_AGARIO_APP_H
#define ZPR_AGARIO_APP_H

#include "seasocks/Server.h"
#include "Blob.h"
#include "Game.h"

using namespace seasocks;

class App : public WebSocket::Handler {
public:
    explicit App(Server* server, Game &game);

    void onConnect(WebSocket* connection) override;

    void onData(WebSocket* connection, const char* data) override;

    void onDisconnect(WebSocket* connection) override;

private:
    std::set<WebSocket*> _connections;
    Server* _server;
    Game _game;
};

#endif //ZPR_AGARIO_APP_H
