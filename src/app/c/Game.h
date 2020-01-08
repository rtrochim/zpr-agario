#ifndef ZPR_AGARIO_GAME_H
#define ZPR_AGARIO_GAME_H

#include "Blob.h"
#include <vector>
#include <map>

#include "lib/json.hpp"
#include "lib/sqlite_modern_cpp.h"

using namespace sqlite;
using namespace nlohmann;

class Game {
public:
    explicit Game(database &&db);

    void login(json &payload, json &response);

    void eatGameBlob(json &payload, json &response);

    void update(json &payload, json &response);

    void eatUserBlob(json &payload, json &response);

    void logout(json &payload);

    void createGameBlobs(json &payload);

    int loginExistingUser(json &payload);

    void createNewUser(json &payload);
private:
    std::vector<Blob> _userBlobs;
    std::vector<Blob> _gameBlobs;
    std::map<std::string, int> _scores;
    database _db;
};


#endif //ZPR_AGARIO_GAME_H
