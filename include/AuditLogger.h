#ifndef AUDIT_LOGGER_H
#define AUDIT_LOGGER_H

#include <string>

class AuditLogger {
private:
    std::string logPath;

public:
    explicit AuditLogger(const std::string& path);

    void logEvent(
        const std::string& operation,
        const std::string& path,
        const std::string& status
    ) const;
};

#endif
