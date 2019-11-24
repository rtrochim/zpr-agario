#include "seasocks/SynchronousResponse.h"
#include "seasocks/ToString.h"
#include "seasocks/StringUtil.h"

using namespace seasocks;

void SynchronousResponse::handle(std::shared_ptr<ResponseWriter> writer) {
    auto rc = responseCode();
    if (!isOk(rc)) {
        writer->error(rc, std::string(payload(), payloadSize()));
        return;
    }

    writer->begin(responseCode());

    writer->header("Content-Length", toString(payloadSize()));
    writer->header("Content-Type", contentType());
    writer->header("Connection", keepConnectionAlive() ? "keep-alive" : "close");
    writer->header("Last-Modified", now());
    writer->header("Pragma", "no-cache");

    auto headers = getAdditionalHeaders();

    if (headers.find("Cache-Control") == headers.end()) {
        writer->header("Cache-Control", "no-store");
    }

    if (headers.find("Expires") == headers.end()) {
        writer->header("Expires", now());
    }

    for (auto& header : headers) {
        writer->header(header.first, header.second);
    }

    writer->payload(payload(), payloadSize());

    writer->finish(keepConnectionAlive());
}

void SynchronousResponse::cancel() {
}
