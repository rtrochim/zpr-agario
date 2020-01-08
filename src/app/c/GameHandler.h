//
// Created by radek on 08.01.2020.
//

#ifndef ZPR_AGARIO_GAMEHANDLER_H
#define ZPR_AGARIO_GAMEHANDLER_H

#include "seasocks/Server.h"
#include "seasocks/StringUtil.h"
#include <iostream>
#include <set>
#include <string>
#include <map>
#include "lib/json.hpp"
#include "lib/sqlite_modern_cpp.h"
#include "Blob.h"

using namespace seasocks;
using namespace sqlite;
using namespace nlohmann;


class GameHandler : public WebSocket::Handler {
public:
    explicit GameHandler(Server* server, database &db);

    void onConnect(WebSocket* connection) override;

    void onData(WebSocket* connection, const char* data) override;

    void onDisconnect(WebSocket* connection) override;
private:
    std::set<WebSocket*> _connections;
    Server* _server;
    database _db;
    std::vector<Blob> _userBlobs;
    std::vector<Blob> _gameBlobs;
    std::map<std::string, int> _scores;

    void handleLogin(json &payload, json &response);

    void handleEatGameBlob(json &payload, json &response);

    void handleUpdate(json &payload, json &response);

    void handleEatUserBlob(json &payload, json &response);

    void handleLogout(json &payload);

    void createGameBlobs(json &payload);

    int loginExistingUser(json &payload);

    void createNewUser(json &payload);


};

#endif //ZPR_AGARIO_GAMEHANDLER_H
