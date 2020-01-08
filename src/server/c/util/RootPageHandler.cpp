#include "seasocks/util/RootPageHandler.h"

#include "seasocks/Request.h"
#include "seasocks/Response.h"
#include "seasocks/util/CrackedUri.h"

using namespace seasocks;

RootPageHandler::RootPageHandler() = default;

RootPageHandler::~RootPageHandler() = default;

CrackedUriPageHandler::Ptr RootPageHandler::add(const CrackedUriPageHandler::Ptr& handler) {
    _handlers.emplace_back(handler);
    return _handlers.back();
}

std::shared_ptr<Response> RootPageHandler::handle(const Request& request) {
    CrackedUri uri(request.getRequestUri());
    for (const auto& it : _handlers) {
        auto response = it->handle(uri, request);
        if (response != Response::unhandled()) {
            return response;
        }
    }
    return Response::unhandled();
}
