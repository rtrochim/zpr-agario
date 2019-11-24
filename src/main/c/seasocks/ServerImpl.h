#pragma once

#include "seasocks/WebSocket.h"

#include <string>

namespace seasocks {

class Connection;
class Request;
class Response;
class Server;

// Internal implementation used to give access to internals to Connections.
class ServerImpl {
public:
    virtual ~ServerImpl() = default;

    virtual void remove(Connection* connection) = 0;
    virtual bool subscribeToWriteEvents(Connection* connection) = 0;
    virtual bool unsubscribeFromWriteEvents(Connection* connection) = 0;
    virtual const std::string& getStaticPath() const = 0;
    virtual std::shared_ptr<WebSocket::Handler> getWebSocketHandler(const char* endpoint) const = 0;
    virtual bool isCrossOriginAllowed(const std::string& endpoint) const = 0;
    virtual std::shared_ptr<Response> handle(const Request& request) = 0;
    virtual std::string getStatsDocument() const = 0;
    virtual void checkThread() const = 0;
    virtual Server& server() = 0;
    virtual size_t clientBufferSize() const = 0;
};

}
