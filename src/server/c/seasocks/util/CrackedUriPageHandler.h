#pragma once

#include "seasocks/Request.h"
#include "seasocks/Response.h"
#include "seasocks/util/CrackedUri.h"

#include <memory>

namespace seasocks {

class CrackedUriPageHandler {
public:
    virtual ~CrackedUriPageHandler() = default;

    virtual std::shared_ptr<Response> handle(const CrackedUri& uri, const Request& request) = 0;

    using Ptr = std::shared_ptr<CrackedUriPageHandler>;
};

}
