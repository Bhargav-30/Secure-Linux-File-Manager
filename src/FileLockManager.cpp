#include "FileLockManager.h"

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/file.h>
#include <unistd.h>

FileLockManager::~FileLockManager()
{
    for (const auto& item : lockedFiles) {
        flock(item.second, LOCK_UN);
        close(item.second);
    }
}

bool FileLockManager::lockFile(
    const std::string& path)
{
    if (lockedFiles.count(path)) {
        std::cerr
            << "File is already locked.\n";
        return false;
    }

    int fd = open(path.c_str(), O_RDWR);

    if (fd == -1) {
        std::cerr << "open() failed: "
                  << std::strerror(errno) << '\n';
        return false;
    }

    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        std::cerr << "File could not be locked: "
                  << std::strerror(errno) << '\n';

        close(fd);
        return false;
    }

    lockedFiles[path] = fd;

    return true;
}

bool FileLockManager::unlockFile(
    const std::string& path)
{
    auto it = lockedFiles.find(path);

    if (it == lockedFiles.end()) {
        std::cerr
            << "File is not locked.\n";
        return false;
    }

    if (flock(it->second, LOCK_UN) == -1) {
        std::cerr << "flock() unlock failed: "
                  << std::strerror(errno) << '\n';
        return false;
    }

    close(it->second);
    lockedFiles.erase(it);

    return true;
}

bool FileLockManager::isLocked(
    const std::string& path) const
{
    return lockedFiles.count(path) > 0;
}
