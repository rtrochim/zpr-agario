#include "Game.h"

#include <memory>
#include <utility>

Game::Game(database &&db) : _db(std::move(db)) {}

void Game::login(const json &payload, json &response) {
    response["highscore"] = 0;
    // Try to get existing user from database, if failed, create new one
    try {
        response["highscore"] = loginExistingUser(payload);
    } catch (sqlite::sqlite_exception& e) {
        createNewUser(payload);
    }
    _scores[payload["id"]] = 0;
    // Create user blob
    _userBlobs.push_back(*(new UserBlob(
            std::string(payload["id"]),
            std::string(payload["x"]),
            std::string(payload["y"]),
            std::string(payload["r"]),
            std::string(payload["username"])
            )));
    // If this is the first user, create game blobs as well
    if (_gameBlobs.empty()) {
        createGameBlobs(payload);
    }
    for(const auto &gameBlob : _gameBlobs){
        response["gameBlobs"].push_back({
            {"id",gameBlob.getId()},
            {"x", gameBlob.getX()},
            {"y", gameBlob.getY()},
            {"r", gameBlob.getRadius()}
        });
    }
    response["messageType"] = "loggedIn";
}

void Game::eatGameBlob(const json &payload, json &response) {
    // Game blob being eaten
    const int gameBlobId = payload["gameBlobId"];
    // Player eating the blob
    _scores[payload["id"]] += 1;
    _gameBlobs.erase(_gameBlobs.begin() + gameBlobId);
    // Send update to client
    for(const auto &userBlob : _userBlobs) {
        response["blobs"].push_back({
            {"id", userBlob.getId()},
            {"x", userBlob.getX()},
            {"y", userBlob.getY()},
            {"r", userBlob.getRadius()},
            {"username", userBlob.getUsername()}
        });
    }
    for(const auto &gameBlob : _gameBlobs){
        response["gameBlobs"].push_back({
            {"id",gameBlob.getId()},
            {"x", gameBlob.getX()},
            {"y", gameBlob.getY()},
            {"r", gameBlob.getRadius()}
        });
    }
    response["score"] = _scores[payload["id"]];
    response["messageType"] = "update";
}

void Game::update(const json &payload, json &response){
    for(auto &userBlob : _userBlobs) {
        // Update server knowledge about player sending the message
        if(userBlob.getId() == payload["id"]){
            userBlob.setX(std::string(payload["x"]));
            userBlob.setY(std::string(payload["y"]));
            userBlob.setRadius(std::string(payload["r"]));
            userBlob.setUsername(std::string(payload["username"]));
        }
        response["blobs"].push_back({
            {"id", userBlob.getId()},
            {"x", userBlob.getX()},
            {"y", userBlob.getY()},
            {"r", userBlob.getRadius()},
            {"username", userBlob.getUsername()}
        });
    }
    for(const auto &gameBlob : _gameBlobs){
        response["gameBlobs"].push_back({
            {"id",gameBlob.getId()},
            {"x", gameBlob.getX()},
            {"y", gameBlob.getY()},
            {"r", gameBlob.getRadius()}
        });
    }
    response["messageType"] = "update";
    response["score"] = _scores[payload["id"]];
}

void Game::eatUserBlob(const json &payload, json &response){
    // User blob being eaten
    const std::string userBlobId = payload["userBlobId"];
    const auto it = std::remove_if(_userBlobs.begin(), _userBlobs.end(), [&userBlobId](UserBlob& userBlob) { return userBlob.getId() == userBlobId; });
    // Radius of the eaten blob
    const std::string eatenRadius = _userBlobs[it - _userBlobs.begin()].getRadius();
    _scores[payload["id"]] += static_cast<int>(std::atof(eatenRadius.c_str()));
    _userBlobs.erase(it, _userBlobs.end());
    for(const auto &userBlob : _userBlobs) {
        response["blobs"].push_back({
            {"id", userBlob.getId()},
            {"x", userBlob.getX()},
            {"y", userBlob.getY()},
            {"r", userBlob.getRadius()},
            {"username", userBlob.getUsername()}});
    }
    for(const auto &gameBlob : _gameBlobs){
        response["gameBlobs"].push_back({
            {"id",gameBlob.getId()},
            {"x", gameBlob.getX()},
            {"y", gameBlob.getY()},
            {"r", gameBlob.getRadius()}
        });
    }
    response["messageType"] = "update";
    response["score"] = _scores[payload["id"]];
}

void Game::logout(const json &payload){
    const std::string username = payload["username"];
    const std::string socketId = payload["id"];
    int highscore;
    // Check if obtained highscore is greater than previous
    _db << "select highscore from players where name = ?" << username >> highscore;
    if(highscore < _scores[socketId]){
        _db << "update players set highscore = ?, active = 0 where name = ?" << _scores[socketId] << username;
    } else {
        _db << "update players set active = 0 where name = ?" << username;
    }
    const auto it = std::remove_if(_userBlobs.begin(), _userBlobs.end(), [&socketId](UserBlob &userBlob) { return userBlob.getId() == socketId; });
    _userBlobs.erase(it, _userBlobs.end());
}

void Game::createGameBlobs(const json &payload) {
    const int width = std::stoi(payload["width"].dump());
    const int height = std::stoi(payload["height"].dump());
    // Create a fixed number of game blobs with random position x: <-width, width>, y: <-height, height>
    for (int i = 0; i < GAME_BLOBS_NUMBER; i++) {
        std::string posX = std::to_string(-width + (std::rand() % (2 * width + 1)));
        std::string posY = std::to_string(-height + (std::rand() % (2 * height + 1)));
        _gameBlobs.push_back(*(new Blob(std::to_string(i), posX, posY, "4")));
    }
}

int Game::loginExistingUser(const json &payload) {
    int highscore;
    _db << "select highscore from players where name = ?" << std::string(payload["username"]) >> highscore;
    _db << "update players set socketId = ?, active = 1 where name = ?" << std::string(payload["id"])
        << std::string(payload["username"]);
    return highscore;
}

void Game::createNewUser(const json &payload){
    _db << "insert into 'players' (socketId, name, active) values (?,?,?);"
        << std::string(payload["id"])
        << std::string(payload["username"])
        << 1;
}

