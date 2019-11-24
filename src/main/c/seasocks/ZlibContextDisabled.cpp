#include "seasocks/ZlibContext.h"

#include <stdexcept>

namespace seasocks {

struct ZlibContext::Impl {
};

ZlibContext::ZlibContext() {
}

ZlibContext::~ZlibContext() {
}

void ZlibContext::initialise(int, int, int) {
    throw std::runtime_error("Not compiled with zlib support");
}

void ZlibContext::deflate(const uint8_t*, size_t, std::vector<uint8_t>&) {
    throw std::runtime_error("Not compiled with zlib support");
}

bool ZlibContext::inflate(std::vector<uint8_t>&, std::vector<uint8_t>&, int&) {
    throw std::runtime_error("Not compiled with zlib support");
}

}