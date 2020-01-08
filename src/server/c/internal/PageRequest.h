#pragma once

#include "internal/HeaderMap.h"
#include "seasocks/Request.h"

#include <unordered_map>
#include <vector>

namespace seasocks {

class PageRequest : public Request {
    std::shared_ptr<Credentials> _credentials;
    const sockaddr_in _remoteAddress;
    const std::string _requestUri;
    Server& _server;
    const Verb _verb;
    std::vector<uint8_t> _content;
    HeaderMap _headers;
    const size_t _contentLength;

public:
    PageRequest(
        const sockaddr_in& remoteAddress,
        const std::string& requestUri,
        Server& server,
        Verb verb,
        HeaderMap&& headers);

    virtual Server& server() const override {
        return _server;
    }

    virtual Verb verb() const override {
        return _verb;
    }

    virtual std::shared_ptr<Credentials> credentials() const override {
        return _credentials;
    }

    virtual const sockaddr_in& getRemoteAddress() const override {
        return _remoteAddress;
    }

    virtual const std::string& getRequestUri() const override {
        return _requestUri;
    }

    virtual size_t contentLength() const override {
        return _contentLength;
    }

    virtual const uint8_t* content() const override {
        return _contentLength > 0 ? &_content[0] : nullptr;
    }

    virtual bool hasHeader(const std::string& name) const override {
        return _headers.find(name) != _headers.end();
    }

    virtual std::string getHeader(const std::string& name) const override {
        auto iter = _headers.find(name);
        return iter == _headers.end() ? std::string() : iter->second;
    }

    bool consumeContent(std::vector<uint8_t>& buffer);

    size_t getUintHeader(const std::string& name) const;
};

} // namespace zpr-agario
