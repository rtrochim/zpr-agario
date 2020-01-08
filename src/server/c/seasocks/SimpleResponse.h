#pragma once

#include "seasocks/StreamingResponse.h"

namespace seasocks {

class SimpleResponse : public StreamingResponse {
    ResponseCode _responseCode;
    std::shared_ptr<std::istream> _stream;
    const Headers _headers;
    const bool _keepAlive;
    const bool _flushInstantly;
    const size_t _bufferSize;
    const TransferEncoding _transferEncoding;

public:
    static constexpr size_t DefaultBufferSize = 16 * 1024 * 1024u;

    SimpleResponse(ResponseCode responseCode, std::shared_ptr<std::istream> stream,
                   const Headers& headers, bool keepAlive = true, bool flushInstantly = false,
                   size_t bufferSize = DefaultBufferSize,
                   TransferEncoding transferEncoding = TransferEncoding::Raw)
            : _responseCode(responseCode), _stream(stream), _headers(headers),
              _keepAlive(keepAlive), _flushInstantly(flushInstantly),
              _bufferSize(bufferSize), _transferEncoding(transferEncoding) {
    }

    virtual std::shared_ptr<std::istream> getStream() const override {
        return _stream;
    }

    virtual Headers getHeaders() const override {
        return _headers;
    }

    virtual ResponseCode responseCode() const override {
        return _responseCode;
    }

    virtual bool keepConnectionAlive() const override {
        return _keepAlive;
    }

    virtual bool flushInstantly() const override {
        return _flushInstantly;
    }

    virtual size_t getBufferSize() const override {
        return _bufferSize;
    }

    virtual TransferEncoding transferEncoding() const override {
        return _transferEncoding;
    }
};

}
