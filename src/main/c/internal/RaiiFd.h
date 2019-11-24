#pragma once

#include <unistd.h>

namespace seasocks {

class RaiiFd {
    int fd_;

public:
    explicit RaiiFd(int fd)
            : fd_(fd) {
    }

    RaiiFd(const RaiiFd&) = delete;
    RaiiFd& operator=(const RaiiFd&) = delete;

    ~RaiiFd() {
        if (fd_ != -1) {
            ::close(fd_);
        }
    }

    bool ok() const {
        return fd_ != -1;
    }

    operator int() const {
        return fd_;
    }
};

}
