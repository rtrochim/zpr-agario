#pragma once

#include "seasocks/ResponseCode.h"

#include <map>
#include <memory>
#include <string>

namespace seasocks {

class ResponseWriter;

class Response {
public:
    virtual ~Response() = default;
    virtual void handle(std::shared_ptr<ResponseWriter> writer) = 0;

    // Called when the connection this response is being sent on is closed.
    virtual void cancel() = 0;

    static std::shared_ptr<Response> unhandled();

    static std::shared_ptr<Response> notFound();

    static std::shared_ptr<Response> error(ResponseCode code, const std::string& error);

    static std::shared_ptr<Response> textResponse(const std::string& response);
    static std::shared_ptr<Response> jsonResponse(const std::string& response);
    static std::shared_ptr<Response> htmlResponse(const std::string& response);
};

}
