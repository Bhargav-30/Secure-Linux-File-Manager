#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>

class FileManager {
private:
    std::string basePath;

    std::string getFullPath(const std::string& filename) const;

public:
    explicit FileManager(const std::string& path);

    bool createFile(const std::string& filename,
                    const std::string& content);

    bool readFile(const std::string& filename,
                  std::string& content);

    std::vector<std::string> listFiles() const;

    bool deleteFile(const std::string& filename);
};

#endif
