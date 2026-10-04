#include <iostream>
#include <string>
#include <filesystem>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

namespace fs = std::filesystem;

const std::string VAULT_DIR = "vault";

void createVault() {
    struct stat st{};

    if (stat(VAULT_DIR.c_str(), &st) != 0) {
        if (mkdir(VAULT_DIR.c_str(), 0700) != 0) {
            perror("mkdir");
            return;
        }
    }
}

void storeFile() {
    std::string filename;

    std::cout << "\nEnter file path: ";
    std::cin >> filename;

    int source = open(filename.c_str(), O_RDONLY);

    if (source < 0) {
        perror("Unable to open source file");
        return;
    }

    std::string destination = VAULT_DIR + "/" + fs::path(filename).filename().string();

    int target = open(
        destination.c_str(),
        O_WRONLY | O_CREAT | O_TRUNC,
        0600
    );

    if (target < 0) {
        perror("Unable to create vault file");
        close(source);
        return;
    }

    char buffer[4096];
    ssize_t bytesRead;

    while ((bytesRead = read(source, buffer, sizeof(buffer))) > 0) {
        ssize_t totalWritten = 0;

        while (totalWritten < bytesRead) {
            ssize_t bytesWritten = write(
                target,
                buffer + totalWritten,
                bytesRead - totalWritten
            );

            if (bytesWritten < 0) {
                perror("Write error");
                close(source);
                close(target);
                return;
            }

            totalWritten += bytesWritten;
        }
    }

    if (bytesRead < 0) {
        perror("Read error");
    } else {
        std::cout << "File stored successfully.\n";
    }

    close(source);
    close(target);
}

void listFiles() {
    std::cout << "\nFiles in vault:\n";

    bool found = false;

    for (const auto& entry : fs::directory_iterator(VAULT_DIR)) {
        std::cout << "- "
                  << entry.path().filename().string()
                  << '\n';
        found = true;
    }

    if (!found) {
        std::cout << "Vault is empty.\n";
    }
}

void retrieveFile() {
    std::string filename;

    std::cout << "\nEnter file name: ";
    std::cin >> filename;

    std::string sourcePath = VAULT_DIR + "/" + filename;

    int source = open(sourcePath.c_str(), O_RDONLY);

    if (source < 0) {
        perror("Unable to open vault file");
        return;
    }

    std::string outputPath = "retrieved_" + filename;

    int target = open(
        outputPath.c_str(),
        O_WRONLY | O_CREAT | O_TRUNC,
        0600
    );

    if (target < 0) {
        perror("Unable to create output file");
        close(source);
        return;
    }

    char buffer[4096];
    ssize_t bytesRead;

    while ((bytesRead = read(source, buffer, sizeof(buffer))) > 0) {
        ssize_t totalWritten = 0;

        while (totalWritten < bytesRead) {
            ssize_t bytesWritten = write(
                target,
                buffer + totalWritten,
                bytesRead - totalWritten
            );

            if (bytesWritten < 0) {
                perror("Write error");
                close(source);
                close(target);
                return;
            }

            totalWritten += bytesWritten;
        }
    }

    if (bytesRead < 0) {
        perror("Read error");
    } else {
        std::cout << "File retrieved successfully as: "
                  << outputPath << '\n';
    }

    close(source);
    close(target);
}

void deleteFile() {
    std::string filename;

    std::cout << "\nEnter file name: ";
    std::cin >> filename;

    std::string path = VAULT_DIR + "/" + filename;

    if (unlink(path.c_str()) != 0) {
        perror("Unable to delete file");
        return;
    }

    std::cout << "File deleted successfully.\n";
}

int main() {

    createVault();

    while (true) {

        std::cout << "\n====================================\n";
        std::cout << "        SECURE LINUX FILE VAULT\n";
        std::cout << "====================================\n";
        std::cout << "1. Store File\n";
        std::cout << "2. Retrieve File\n";
        std::cout << "3. List Files\n";
        std::cout << "4. Delete File\n";
        std::cout << "5. Exit\n";
        std::cout << "====================================\n";

        int choice;

        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {

            case 1:
                storeFile();
                break;

            case 2:
                retrieveFile();
                break;

            case 3:
                listFiles();
                break;

            case 4:
                deleteFile();
                break;

            case 5:
                std::cout << "Exiting vault...\n";
                return 0;

            default:
                std::cout << "Invalid choice.\n";
        }
    }
}