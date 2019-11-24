#pragma once

#include "seasocks/Logger.h"

#include <cstdio>

namespace seasocks {

class PrintfLogger : public Logger {
public:
    explicit PrintfLogger(Level minLevelToLog_ = Level::Debug)
            : minLevelToLog(minLevelToLog_) {
    }

    ~PrintfLogger() = default;

    virtual void log(Level level, const char* message) override {
        if (level >= minLevelToLog) {
            printf("%s: %s\n", levelToString(level), message);
        }
    }

    Level minLevelToLog;
};

} // namespace zpr-agario
