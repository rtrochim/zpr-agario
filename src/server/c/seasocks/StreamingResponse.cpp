#include "seasocks/StreamingResponse.h"
#include "seasocks/ToString.h"
#include "seasocks/StringUtil.h"

using namespace seasocks;

void StreamingResponse::handle(std::shared_ptr<ResponseWriter> writer) {
    writer->begin(responseCode(), transferEncoding());

    auto headers = getHeaders();
    for (auto& header : headers) {
        writer->header(header.first, header.second);
    }

    std::shared_ptr<std::istream> stream = getStream();

    auto bufSize = getBufferSize();
    bool flush = flushInstantly();
    std::unique_ptr<char[]> buffer(new char[bufSize]);

    while (!closed) {
        // blocks until buffer is full or eof is reached
        stream->read(buffer.get(), bufSize);

        bool isEof = stream->eof();
        bool isGood = stream->good();
        if (isGood || isEof) {
            // everything is fine, push data to client
            writer->payload(buffer.get(), stream->gcount(), flush);
        }

        if (!isGood) {
            // EOF or error occured
            // ignore the error since we can't access it
            closed = true;
        }
    };

    writer->finish(keepConnectionAlive());
}

void StreamingResponse::cancel() {
    closed = true;
}
