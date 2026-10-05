#ifndef FILE_LOCK_MANAGER_H
#define FILE_LOCK_MANAGER_H

#include <string>
#include <unordered_map>

class FileLockManager {
private:
    std::unordered_map<std::string, int> lockedFiles;

public:
    ~FileLockManager();

    bool lockFile(const std::string& path);

    bool unlockFile(const std::string& path);

    bool isLocked(const std::string& path) const;
};

#endif