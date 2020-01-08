#include "seasocks/Request.h"

#include <cstring>

namespace seasocks {

const char* Request::name(Verb v) {
    switch (v) {
        case Verb::Invalid:
            return "Invalid";
        case Verb::WebSocket:
            return "WebSocket";
        case Verb::Get:
            return "Get";
        case Verb::Put:
            return "Put";
        case Verb::Post:
            return "Post";
        case Verb::Delete:
            return "Delete";
        case Verb::Head:
            return "Head";
        case Verb::Options:
            return "Options";
        default:
            return "???";
    }
}

Request::Verb Request::verb(const char* verb) {
    if (std::strcmp(verb, "GET") == 0)
        return Request::Verb::Get;
    if (std::strcmp(verb, "PUT") == 0)
        return Request::Verb::Put;
    if (std::strcmp(verb, "POST") == 0)
        return Request::Verb::Post;
    if (std::strcmp(verb, "DELETE") == 0)
        return Request::Verb::Delete;
    if (std::strcmp(verb, "HEAD") == 0)
        return Request::Verb::Head;
    if (std::strcmp(verb, "OPTIONS") == 0)
        return Request::Verb::Options;
    return Request::Verb::Invalid;
}

} // namespace zpr-agario
