#include "AuditLogger.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>

AuditLogger::AuditLogger(
    const std::string& path)
    : logPath(path) {
}

void AuditLogger::logEvent(
    const std::string& operation,
    const std::string& path,
    const std::string& status) const {

    std::ofstream logFile(
        logPath,
        std::ios::app
    );

    if (!logFile) {
        return;
    }

    auto now =
        std::chrono::system_clock::now();

    std::time_t time =
        std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};

    localtime_r(
        &time,
        &localTime
    );

    logFile
        << std::put_time(
               &localTime,
               "%Y-%m-%d %H:%M:%S")
        << " | "
        << operation
        << " | "
        << path
        << " | "
        << status
        << '\n';
}
