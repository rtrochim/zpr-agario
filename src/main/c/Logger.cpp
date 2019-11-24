#include "internal/Debug.h"

#include "seasocks/Logger.h"

#include <cstdarg>
#include <cstdio>

namespace seasocks {

constexpr int MAX_MESSAGE_LENGTH = 1024;

#define PRINT_TO_MESSAGEBUF()                                 \
    char messageBuf[MAX_MESSAGE_LENGTH];                      \
    va_list args;                                             \
    va_start(args, message);                                  \
    vsnprintf(messageBuf, MAX_MESSAGE_LENGTH, message, args); \
    va_end(args)

void Logger::debug(const char* message, ...) {
#ifdef LOG_DEBUG_INFO
    PRINT_TO_MESSAGEBUF();
    log(Level::Debug, messageBuf);
#else
    (void) message;
#endif
}

void Logger::access(const char* message, ...) {
    PRINT_TO_MESSAGEBUF();
    log(Level::Access, messageBuf);
}

void Logger::info(const char* message, ...) {
    PRINT_TO_MESSAGEBUF();
    log(Level::Info, messageBuf);
}

void Logger::warning(const char* message, ...) {
    PRINT_TO_MESSAGEBUF();
    log(Level::Warning, messageBuf);
}

void Logger::error(const char* message, ...) {
    PRINT_TO_MESSAGEBUF();
    log(Level::Error, messageBuf);
}

void Logger::severe(const char* message, ...) {
    PRINT_TO_MESSAGEBUF();
    log(Level::Severe, messageBuf);
}

} // namespace zpr-agario
