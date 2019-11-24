#pragma once

#include "seasocks/Response.h"
#include "seasocks/ResponseWriter.h"

namespace seasocks {

class SynchronousResponse : public Response {
public:
    virtual ~SynchronousResponse() = default;
    virtual void handle(std::shared_ptr<ResponseWriter> writer) override;
    virtual void cancel() override;

    virtual ResponseCode responseCode() const = 0;

    virtual const char* payload() const = 0;
    virtual size_t payloadSize() const = 0;

    virtual std::string contentType() const = 0;

    virtual bool keepConnectionAlive() const = 0;

    typedef std::multimap<std::string, std::string> Headers;
    virtual Headers getAdditionalHeaders() const = 0;
};

}