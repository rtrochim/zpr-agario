#include "internal/PageRequest.h"

#include <cstdlib>
#include <cstring>

namespace seasocks {

PageRequest::PageRequest(
    const sockaddr_in& remoteAddress,
    const std::string& requestUri,
    Server& server,
    Verb verb,
    HeaderMap&& headers)
        : _credentials(std::make_shared<Credentials>()),
          _remoteAddress(remoteAddress),
          _requestUri(requestUri),
          _server(server),
          _verb(verb),
          _headers(std::move(headers)),
          _contentLength(getUintHeader("Content-Length")) {
}

bool PageRequest::consumeContent(std::vector<uint8_t>& buffer) {
    if (buffer.size() < _contentLength) {
        return false;
    }
    if (buffer.size() == _contentLength) {
        _content.swap(buffer);
    } else {
        _content.assign(buffer.begin(), buffer.begin() + _contentLength);
        buffer.erase(buffer.begin(), buffer.begin() + _contentLength);
    }
    return true;
}

size_t PageRequest::getUintHeader(const std::string& name) const {
    const auto iter = _headers.find(name);
    if (iter == _headers.end()) {
        return 0u;
    }
    const auto val = std::stoi(iter->second);
    if (val < 0) {
        return 0u;
    }
    return static_cast<size_t>(val);
}

} // namespace zpr-agario
