#ifndef ZPR_AGARIO_GAME_H
#define ZPR_AGARIO_GAME_H

#include "UserBlob.h"
#include <vector>
#include <map>

#include "lib/json.hpp"
#include "lib/sqlite_modern_cpp.h"

using namespace sqlite;
using namespace nlohmann;

/**
 *  @file   Game.h
 *  @brief  Class representing a single game with all of the data & users associated with it
 *  @author Radek Trochimiuk & Dominik Ajlert
 *  @date   2020-01-01
 ***********************************************/
class Game {
public:
    static const int GAME_BLOBS_NUMBER = 500; /*!< Number of game blobs created when the game starts  */

    /**
    *  @brief Create a Game object with db instance associated with it
    *  @param[in]   db   Reference on a databse instance, that will be storing the state of a given Game
    ************************************************************/
    explicit Game(database &db);

    /**
    *  @brief Get's called upon a user login
    *  @param[in]   payload     JSON object containing all necessary user's data, like username and UserBlob's coordinates
    *  @param[in]   response    JSON object that will be filled with all the data associated with a specific user
    *  @return      void
    ************************************************************/
    void login(json &payload, json &response);

    /**
    *  @brief Get's called when a user notifies the Game that he's eaten a particular GameBlob
    *  @param[in]   payload     JSON object containing all necessary user's data, like username, UserBlob's coordinates and information about an eaten GameBlob
    *  @param[in]   response    JSON object that will be filled with all the data associated with a specific user
    *  @return      void
    ************************************************************/
    void eatGameBlob(json &payload, json &response);

    void update(json &payload, json &response);

    /**
    *  @brief Get's called when a user notifies the Game that he's eaten a particular UserBlob
    *  @param[in]   payload     JSON object containing all necessary user's data, like username, UserBlob's coordinates and information about an eaten UserBlob
    *  @param[in]   response    JSON object that will be filled with all the data associated with a specific user
    *  @return      void
    ************************************************************/
    void eatUserBlob(json &payload, json &response);

    /**
    *  @brief Get's called right before a user disconnects from the current Game
    *  @param[in]   payload     JSON object containing all necessary user's data, like username and UserBlob's last coordinates
    *  @return      void
    ************************************************************/
    void logout(json &payload);

private:
    /**
    *  @brief Get's called if the _gameBlobs vector has not been initiated beforehand
    *  @param[in]   payload     JSON object containing width and height of the canvas being used
    *  @return      void
    ************************************************************/
    void createGameBlobs(json &payload);

    /**
    *  @brief Get's called when a registered user tries to log in
    *  @param[in]   payload     JSON object containing user's id and username
    *  @return      int         Highscore of a given user
    ************************************************************/
    int loginExistingUser(json &payload);

    /**
    *  @brief Get's called when a new user tries to log in for the first time
    *  @param[in]   payload     JSON object containing user's id and username
    *  @return      void
    ************************************************************/
    void createNewUser(json &payload);

    std::vector<UserBlob> _userBlobs; /*!< Vector that stores information about user blobs */
    std::vector<Blob> _gameBlobs; /*!< Vector that stores information about game blobs */
    std::map<std::string, int> _scores; /*!< Map that stores information about a given user (distinguished by their's id) and his current score */
    database _db; /*!< Database instance. Stores all the game and user's data  */
};


#endif //ZPR_AGARIO_GAME_H
