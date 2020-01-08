#pragma once

#include "seasocks/Credentials.h"
#include "seasocks/Response.h"

#include <memory>
#include <string>

namespace seasocks {

class Request;

class PageHandler {
public:
    virtual ~PageHandler() = default;

    virtual std::shared_ptr<Response> handle(const Request& request) = 0;
};

}
