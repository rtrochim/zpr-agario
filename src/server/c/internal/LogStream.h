#pragma once

#include "internal/Debug.h"

// Internal stream helpers for logging.
#include <sstream>

#define LS_LOG(LOG, LEVEL, STUFF)                            \
    {                                                        \
        std::ostringstream os_;                              \
        os_ << STUFF;                                        \
        (LOG)->log(Logger::Level::LEVEL, os_.str().c_str()); \
    }

#define LS_DEBUG(LOG, STUFF) LS_LOG(LOG, Debug, STUFF)
#define LS_ACCESS(LOG, STUFF) LS_LOG(LOG, Access, STUFF)
#define LS_INFO(LOG, STUFF) LS_LOG(LOG, Info, STUFF)
#define LS_WARNING(LOG, STUFF) LS_LOG(LOG, Warning, STUFF)
#define LS_ERROR(LOG, STUFF) LS_LOG(LOG, Error, STUFF)
#define LS_SEVERE(LOG, STUFF) LS_LOG(LOG, Severe, STUFF)
