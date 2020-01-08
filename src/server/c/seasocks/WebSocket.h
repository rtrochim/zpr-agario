#pragma once

#include "seasocks/Request.h"

#include <string>
#include <vector>

namespace seasocks {

class WebSocket : public Request {
public:
    /**
     * Send the given text data. Must be called on the seasocks thread.
     * See Server::execute for how to run work on the seasocks
     * thread externally.
     */
    virtual void send(const char* data) = 0;
    /**
     * Send the given text data. Must be called on the seasocks thread.
     * See Server::execute for how to run work on the seasocks
     * thread externally.
     */
    void send(const std::string& data) {
        send(data.c_str());
    }
    /**
     * Send the given binary data. Must be called on the seasocks thread.
     * See Server::execute for how to run work on the seasocks
     * thread externally.
     */
    virtual void send(const uint8_t* data, size_t length) = 0;
    /**
     * Close the socket. It's invalid to access the socket after
     * calling close(). The Handler::onDisconnect() call may occur
     * at a later time.
     */
    virtual void close() = 0;

    /**
     * Interface to dealing with WebSocket connections.
     */
    class Handler {
    public:
        virtual ~Handler() = default;

        /**
         * Called on the seasocks thread during initial connection.
         */
        virtual void onConnect(WebSocket* connection) = 0;
        /**
         * Called on the seasocks thread with upon receipt of a full text WebSocket message.
         */
        virtual void onData(WebSocket*, const char*) {
        }
        /**
         * Called on the seasocks thread with upon receipt of a full binary WebSocket message.
         */
        virtual void onData(WebSocket*, const uint8_t*, size_t) {
        }
        /**
         * Called on the seasocks thread when the socket has been
         */
        virtual void onDisconnect(WebSocket* connection) = 0;
        /**
         * Choose a protocol before accepting a connection: return < 0 to reject the connection, else return the ordinal
         * in the vector of string protocols.
         */
        virtual ssize_t chooseProtocol(const std::vector<std::string>&) const {
            return 0;
        }
    };

protected:
    // To delete a WebSocket, just close it. It is owned by the Server, and
    // the server will delete it when it's finished.
    virtual ~WebSocket() = default;
};

} // namespace zpr-agario
