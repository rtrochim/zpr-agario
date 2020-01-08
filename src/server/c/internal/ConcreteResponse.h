#pragma once

#include "seasocks/SynchronousResponse.h"

namespace seasocks {

class ConcreteResponse : public SynchronousResponse {
    ResponseCode _responseCode;
    const std::string _payload;
    const std::string _contentType;
    const Headers _headers;
    const bool _keepAlive;

public:
    ConcreteResponse(ResponseCode responseCode, const std::string& payload,
                     const std::string& contentType, const Headers& headers, bool keepAlive)
            : _responseCode(responseCode), _payload(payload), _contentType(contentType),
              _headers(headers), _keepAlive(keepAlive) {
    }

    virtual ResponseCode responseCode() const override {
        return _responseCode;
    }

    virtual const char* payload() const override {
        return _payload.c_str();
    }

    virtual size_t payloadSize() const override {
        return _payload.size();
    }

    virtual bool keepConnectionAlive() const override {
        return _keepAlive;
    }

    virtual std::string contentType() const override {
        return _contentType;
    }

    virtual Headers getAdditionalHeaders() const override {
        return _headers;
    }
};

}
