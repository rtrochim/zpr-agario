#include "internal/ConcreteResponse.h"

#include "seasocks/Response.h"

namespace seasocks {

std::shared_ptr<Response> Response::unhandled() {
    static std::shared_ptr<Response> unhandled;
    return unhandled;
}

std::shared_ptr<Response> Response::notFound() {
    static std::shared_ptr<Response> notFound = std::make_shared<ConcreteResponse>(
        ResponseCode::NotFound,
        "Not found", "text/plain",
        SynchronousResponse::Headers(), false);
    return notFound;
}

std::shared_ptr<Response> Response::error(ResponseCode code, const std::string& error) {
    return std::make_shared<ConcreteResponse>(
        code, error, "text/plain",
        SynchronousResponse::Headers(), false);
}

std::shared_ptr<Response> Response::textResponse(const std::string& response) {
    return std::make_shared<ConcreteResponse>(
        ResponseCode::Ok,
        response, "text/plain",
        SynchronousResponse::Headers(), true);
}

std::shared_ptr<Response> Response::jsonResponse(const std::string& response) {
    return std::make_shared<ConcreteResponse>(
        ResponseCode::Ok, response,
        "application/json",
        SynchronousResponse::Headers(), true);
}

std::shared_ptr<Response> Response::htmlResponse(const std::string& response) {
    return std::make_shared<ConcreteResponse>(
        ResponseCode::Ok, response,
        "text/html",
        SynchronousResponse::Headers(), true);
}

}
