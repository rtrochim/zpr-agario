#pragma once

#include "seasocks/ResponseCode.h"
#include "seasocks/TransferEncoding.h"

#include <string>

namespace seasocks {

// An interface to write a response to a Request. All methods must be called
// from the Seasocks main thread. Safe in the presence of closed connections:
// writes to connections that have closed are silently dropped. Responses that
// wish to take note of closed connections must use their cancel() callback.
class ResponseWriter {
public:
    virtual ~ResponseWriter() = default;

    // Begins a request with the given code. If you want to generate a "normal"
    // zpr-agario error, see 'error' below. After beginning, it is expected you
    // will call 'header' zero or more times, then 'payload' zero or more times,
    // then 'finish' exactly once. Using a transfer encoding other than Raw will
    // automatically cause the appropriate header to be sent.
    virtual void begin(ResponseCode responseCode,
                       TransferEncoding encoding = TransferEncoding::Raw) = 0;
    // Add a header. Must be called after 'begin' and before 'payload'. May be
    // called as many times as needed.
    virtual void header(const std::string& header, const std::string& value) = 0;
    // Add some payload data. Must be called after 'begin' and any 'header' calls.
    // May be called multiple times. The flush parameter controls whether the
    // data should be sent immediately, or buffered to be sent with a subsequent
    // call to 'payload', or 'finish'.
    virtual void payload(const void* data, size_t size, bool flush = true) = 0;
    // Finish a response.
    virtual void finish(bool keepConnectionOpen) = 0;

    // Send an error back to the user. No calls to 'header' or 'payload'
    // or 'finish' should be executed. If you wish to serve your own error document
    // then use the normal 'begin'/'header'/'payload'/'finish' process but with
    // an error code. This routine is to get Seasocks to generate its own error.
    virtual void error(ResponseCode responseCode, const std::string& payload) = 0;
    // Check whether this writer is still active; i.e. the underlying connection
    // is still open.
    virtual bool isActive() const = 0;
};

}
