#include "FileManager.h"

#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

FileManager::FileManager(const std::string& path)
    : basePath(path) {

    if (mkdir(basePath.c_str(), 0755) == -1 &&
        errno != EEXIST) {

        std::cerr << "Could not create data directory: "
                  << std::strerror(errno) << '\n';
    }
}

std::string FileManager::getFullPath(
    const std::string& filename) const {

    return basePath + "/" + filename;
}

bool FileManager::createFile(
    const std::string& filename,
    const std::string& content) {

    if (filename.empty() ||
        filename == "." ||
        filename == ".." ||
        filename.find('/') != std::string::npos) {

        std::cerr << "Invalid filename.\n";
        return false;
    }

    std::string path = getFullPath(filename);

    int fd = open(
        path.c_str(),
        O_WRONLY | O_CREAT | O_TRUNC,
        0644
    );

    if (fd == -1) {
        std::cerr << "open() failed: "
                  << std::strerror(errno) << '\n';
        return false;
    }

    const char* data = content.c_str();
    ssize_t total = 0;
    ssize_t size = static_cast<ssize_t>(content.size());

    while (total < size) {

        ssize_t written =
            write(fd, data + total, size - total);

        if (written == -1) {

            std::cerr << "write() failed: "
                      << std::strerror(errno) << '\n';

            close(fd);
            return false;
        }

        total += written;
    }

    if (close(fd) == -1) {

        std::cerr << "close() failed: "
                  << std::strerror(errno) << '\n';

        return false;
    }

    return true;
}

bool FileManager::readFile(
    const std::string& filename,
    std::string& content) {

    std::string path = getFullPath(filename);

    int fd = open(path.c_str(), O_RDONLY);

    if (fd == -1) {

        std::cerr << "open() failed: "
                  << std::strerror(errno) << '\n';

        return false;
    }

    content.clear();

    char buffer[4096];

    while (true) {

        ssize_t bytes =
            read(fd, buffer, sizeof(buffer));

        if (bytes == 0) {
            break;
        }

        if (bytes == -1) {

            std::cerr << "read() failed: "
                      << std::strerror(errno) << '\n';

            close(fd);
            return false;
        }

        content.append(
            buffer,
            static_cast<std::size_t>(bytes)
        );
    }

    if (close(fd) == -1) {

        std::cerr << "close() failed: "
                  << std::strerror(errno) << '\n';

        return false;
    }

    return true;
}

std::vector<std::string> FileManager::listFiles() const {

    std::vector<std::string> files;

    DIR* directory =
        opendir(basePath.c_str());

    if (directory == nullptr) {

        std::cerr << "opendir() failed: "
                  << std::strerror(errno) << '\n';

        return files;
    }

    while (dirent* entry = readdir(directory)) {

        std::string name = entry->d_name;

        if (name != "." && name != "..") {
            files.push_back(name);
        }
    }

    closedir(directory);

    return files;
}

bool FileManager::deleteFile(
    const std::string& filename) {

    std::string path = getFullPath(filename);

    if (unlink(path.c_str()) == -1) {

        std::cerr << "unlink() failed: "
                  << std::strerror(errno) << '\n';

        return false;
    }

    return true;
}
