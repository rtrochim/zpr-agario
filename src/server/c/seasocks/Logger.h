#pragma once

namespace seasocks {

/**
 * Class to send debug logging information to.
 */
class Logger {
public:
    virtual ~Logger() = default;

    enum class Level {
        Debug,  // NB Debug is usually opted-out of at compile-time.
        Access, // Used to log page requests etc
        Info,
        Warning,
        Error,
        Severe,
    };

    virtual void log(Level level, const char* message) = 0;

    void debug(const char* message, ...);
    void access(const char* message, ...);
    void info(const char* message, ...);
    void warning(const char* message, ...);
    void error(const char* message, ...);
    void severe(const char* message, ...);

    static const char* levelToString(Level level) {
        switch (level) {
            case Level::Debug:
                return "debug";
            case Level::Access:
                return "access";
            case Level::Info:
                return "info";
            case Level::Warning:
                return "warning";
            case Level::Error:
                return "ERROR";
            case Level::Severe:
                return "SEVERE";
            default:
                return "???";
        }
    }
};

} // namespace zpr-agario
