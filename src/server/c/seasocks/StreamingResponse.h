#pragma once

#include "seasocks/Response.h"
#include "seasocks/ResponseWriter.h"
#include "seasocks/TransferEncoding.h"

#include <iosfwd>

namespace seasocks {

// A low level way to write create responses. This class doesn't meddle with or
// assume anything based on the headers.
class StreamingResponse : public Response {
    bool closed = false;

public:
    virtual ~StreamingResponse() = default;
    virtual void handle(std::shared_ptr<ResponseWriter> writer) override;
    virtual void cancel() override;

    virtual std::shared_ptr<std::istream> getStream() const = 0;

    typedef std::multimap<std::string, std::string> Headers;
    virtual Headers getHeaders() const = 0;

    virtual ResponseCode responseCode() const = 0;

    virtual bool keepConnectionAlive() const = 0;
    virtual bool flushInstantly() const = 0;

    virtual size_t getBufferSize() const = 0;
    virtual TransferEncoding transferEncoding() const = 0;
};

}
