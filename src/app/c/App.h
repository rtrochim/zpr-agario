#ifndef ZPR_AGARIO_APP_H
#define ZPR_AGARIO_APP_H

#include "seasocks/Server.h"
#include "Blob.h"
#include "Game.h"

using namespace seasocks;

/**
 *  @file   App.h
 *  @brief  Main Application class for handling socket connections & user data
 *  @author Radek Trochimiuk & Dominik Ajlert
 *  @date   2020-01-01
 ***********************************************/

class App : public WebSocket::Handler {
public:
    /**
    *  @brief Create main application object with given server and game instances.
    *  @param[in]   server   Seasock's Server object
    *  @param[in]   game    Game object storing information about users, scores and handling all database communication process
    ************************************************************/
    explicit App(Server* server, Game &game);

    /**
    *  @brief Get's called upon user join request sent by a given socket
    *  @param[in]   connection   WebSocket connection, which can be further used to communicate with specific user
    *  @return      void
    ************************************************************/
    void onConnect(WebSocket* connection) override;

    /**
    *  @brief Get's called whenever a user tries to send some data via its socket
    *  @param[in]   connection   WebSocket connection, which can be further used to communicate with specific user
    *  @param[in]   data   Data mapped to array of characters structure, containing information from a user
    *  @return      void
    ************************************************************/
    void onData(WebSocket* connection, const char* data) override;

    /**
    *  @brief Get's called whenever a user (and a socket connection associated with them) is going to be terminated
    *  @param[in]   connection   WebSocket connection, which will be terminated
    *  @return      void
    ************************************************************/
    void onDisconnect(WebSocket* connection) override;

private:
    std::set<WebSocket*> _connections; /*!< Set of connections, that can be further used to communicate with all users/players */
    Server* _server; /*!< Seasock's Server instance */
    Game _game; /*!< Game instance */
};

#endif //ZPR_AGARIO_APP_H
