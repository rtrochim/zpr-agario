#include "Game.h"

Game::Game(database &&db) : _db(db) {}

void Game::login(json &payload, json &response) {
    response["highscore"] = 0;
    try {
        response["highscore"] = loginExistingUser(payload);
    } catch (sqlite::sqlite_exception& e) {
        createNewUser(payload);
    }
    _scores[payload["id"]] = 0;
    _userBlobs.push_back(*(new Blob(
            std::string(payload["id"]),
            std::string(payload["x"]),
            std::string(payload["y"]),
            std::string(payload["r"]),
            std::string(payload["username"]))));
    if (_gameBlobs.empty()) {
        createGameBlobs(payload);
    }
    for(auto &gameBlob : _gameBlobs){
        response["gameBlobs"].push_back({
            {"id",gameBlob.getId()},
            {"x", gameBlob.getX()},
            {"y", gameBlob.getY()},
            {"r", gameBlob.getRadius()}});
    }
    response["messageType"] = "loggedIn";
}

void Game::eatGameBlob(json &payload, json &response) {
    int gameBlobId = payload["gameBlobId"];
    std::string blobId = payload["blobId"];
    _scores[payload["blobId"]] += 1;
    _gameBlobs.erase(_gameBlobs.begin() + gameBlobId);
    for(auto &blob : _userBlobs) {
        response["blobs"].push_back({{"id", blob.getId()}, {"x", blob.getX()}, {"y", blob.getY()},{"r", blob.getRadius()}, {"username", blob.getUsername()}});
    }
    for(auto &gameBlob : _gameBlobs){
        response["gameBlobs"].push_back({{"id",gameBlob.getId()},{"x", gameBlob.getX()},{"y", gameBlob.getY()},{"r", gameBlob.getRadius()}});
    }
    response["score"] = _scores[payload["id"]];
    response["messageType"] = "update";
}

void Game::update(json &payload, json &response){
    for(auto &blob : _userBlobs) {
        if(blob.getId() == payload["id"]){
            blob.setX(std::string(payload["x"]));
            blob.setY(std::string(payload["y"]));
            blob.setRadius(std::string(payload["r"]));
            blob.setUsername(std::string(payload["username"]));
        }
        response["blobs"].push_back({{"id", blob.getId()}, {"x", blob.getX()}, {"y", blob.getY()},{"r", blob.getRadius()}, {"username", blob.getUsername()}});
    }
    for(auto &gameBlob : _gameBlobs){
        response["gameBlobs"].push_back({{"id",gameBlob.getId()},{"x", gameBlob.getX()},{"y", gameBlob.getY()},{"r", gameBlob.getRadius()}});
    }
    response["messageType"] = "update";
    response["score"] = _scores[payload["id"]];
}

void Game::eatUserBlob(json &payload, json &response){
    std::string userBlobId = payload["userBlobId"];
    auto it = std::remove_if(_userBlobs.begin(), _userBlobs.end(), [&userBlobId](Blob& obj) { return obj.getId() == userBlobId; });
    std::string eatenRadius = _userBlobs[it - _userBlobs.begin()].getRadius();
    _scores[payload["id"]] += static_cast<int>(std::atof(eatenRadius.c_str()));
    _userBlobs.erase(it, _userBlobs.end());
    for(auto &blob : _userBlobs) {
        response["blobs"].push_back({{"id", blob.getId()}, {"x", blob.getX()}, {"y", blob.getY()},{"r", blob.getRadius()}, {"username", blob.getUsername()}});
    }
    for(auto &gameBlob : _gameBlobs){
        response["gameBlobs"].push_back({{"id",gameBlob.getId()},{"x", gameBlob.getX()},{"y", gameBlob.getY()},{"r", gameBlob.getRadius()}});
    }
    response["messageType"] = "update";
    response["score"] = _scores[payload["id"]];
}

void Game::logout(json &payload){
    std::string username = payload["username"];
    std::string socketId = payload["id"];
    int highscore;
    _db << "select highscore from players where name = ?" << username >> highscore;
    if(highscore < _scores[socketId]){
        _db << "update players set highscore = ?, active = 0 where name = ?" << _scores[socketId] << username;
    } else {
        _db << "update players set active = 0 where name = ?" << username;
    }
    auto it = std::remove_if(_userBlobs.begin(), _userBlobs.end(), [&socketId](Blob& obj) { return obj.getId() == socketId; });
    _userBlobs.erase(it, _userBlobs.end());
}

void Game::createGameBlobs(json &payload) {
    int width = std::stoi(payload["width"].dump());
    int height = std::stoi(payload["height"].dump());
    for (int i = 0; i < 500; i++) {
        std::string posX = std::to_string(-width + (std::rand() % (2 * width + 1)));
        std::string posY = std::to_string(-height + (std::rand() % (2 * height + 1)));
        _gameBlobs.push_back(*(new Blob(std::to_string(i), posX, posY, "4", "null")));
    }
}

int Game::loginExistingUser(json &payload) {
    int highscore;
    _db << "select highscore from players where name = ?" << std::string(payload["username"]) >> highscore;
    _db << "update players set socketId = ?, active = 1 where name = ?" << std::string(payload["id"])
        << std::string(payload["username"]);
    return highscore;
}

void Game::createNewUser(json &payload){
    _db << "insert into 'players' (socketId, name, active) values (?,?,?);"
        << std::string(payload["id"])
        << std::string(payload["username"])
        << 1;
}

