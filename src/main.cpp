#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <iomanip>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <openssl/sha.h>

namespace fs = std::filesystem;

const std::string VAULT_DIR = "vault";
const std::string AUTH_FILE = "config/auth.dat";

// --------------------------------------------------
// SHA-256 PASSWORD HASH
// --------------------------------------------------

std::string hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(
        reinterpret_cast<const unsigned char*>(password.c_str()),
        password.length(),
        hash
    );

    std::stringstream ss;

    for (unsigned char c : hash) {
        ss << std::hex
           << std::setw(2)
           << std::setfill('0')
           << static_cast<int>(c);
    }

    return ss.str();
}

// --------------------------------------------------
// HIDDEN PASSWORD INPUT
// --------------------------------------------------

std::string readPassword() {
    termios oldSettings{};
    termios newSettings{};

    tcgetattr(STDIN_FILENO, &oldSettings);

    newSettings = oldSettings;
    newSettings.c_lflag &= ~ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

    std::string password;
    std::getline(std::cin, password);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);

    std::cout << '\n';

    return password;
}

// --------------------------------------------------
// CREATE VAULT DIRECTORY
// --------------------------------------------------

void createVault() {
    struct stat st{};

    if (stat(VAULT_DIR.c_str(), &st) != 0) {

        if (mkdir(VAULT_DIR.c_str(), 0700) != 0) {
            perror("Unable to create vault");
        }
    }
}

// --------------------------------------------------
// FIRST TIME PASSWORD SETUP
// --------------------------------------------------

bool setupAuthentication() {

    if (fs::exists(AUTH_FILE)) {
        return true;
    }

    std::cout << "\n====================================\n";
    std::cout << "       FIRST TIME SETUP\n";
    std::cout << "====================================\n";

    std::string password;
    std::string confirmPassword;

    std::cout << "Create password: ";
    password = readPassword();

    std::cout << "Confirm password: ";
    confirmPassword = readPassword();

    if (password.empty()) {
        std::cout << "Password cannot be empty.\n";
        return false;
    }

    if (password != confirmPassword) {
        std::cout << "Passwords do not match.\n";
        return false;
    }

    std::ofstream file(AUTH_FILE);

    if (!file) {
        std::cout << "Unable to create authentication file.\n";
        return false;
    }

    file << hashPassword(password);
    file.close();

    chmod(AUTH_FILE.c_str(), 0600);

    std::cout << "Password created successfully.\n";

    return true;
}

// --------------------------------------------------
// LOGIN
// --------------------------------------------------

bool authenticate() {

    std::ifstream file(AUTH_FILE);

    if (!file) {
        std::cout << "Authentication file not found.\n";
        return false;
    }

    std::string storedHash;
    std::getline(file, storedHash);

    file.close();

    for (int attempt = 1; attempt <= 3; ++attempt) {

        std::cout << "\nEnter password: ";

        std::string password = readPassword();

        std::string enteredHash = hashPassword(password);

        if (enteredHash == storedHash) {
            std::cout << "Authentication successful.\n";
            return true;
        }

        std::cout << "Incorrect password.\n";
        std::cout << "Attempts remaining: "
                  << 3 - attempt << '\n';
    }

    std::cout << "\nAccess denied.\n";

    return false;
}

// --------------------------------------------------
// STORE FILE
// --------------------------------------------------

void storeFile() {

    std::string filename;

    std::cout << "\nEnter file path: ";
    std::cin >> filename;

    int source = open(filename.c_str(), O_RDONLY);

    if (source < 0) {
        perror("Unable to open source file");
        return;
    }

    std::string safeName =
        fs::path(filename).filename().string();

    std::string destination =
        VAULT_DIR + "/" + safeName;

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

// --------------------------------------------------
// LIST FILES
// --------------------------------------------------

void listFiles() {

    std::cout << "\nFiles in vault:\n";

    bool found = false;

    for (const auto& entry :
         fs::directory_iterator(VAULT_DIR)) {

        std::cout << "- "
                  << entry.path().filename().string()
                  << '\n';

        found = true;
    }

    if (!found) {
        std::cout << "Vault is empty.\n";
    }
}

// --------------------------------------------------
// RETRIEVE FILE
// --------------------------------------------------

void retrieveFile() {

    std::string filename;

    std::cout << "\nEnter file name: ";
    std::cin >> filename;

    std::string sourcePath =
        VAULT_DIR + "/" + filename;

    int source = open(sourcePath.c_str(), O_RDONLY);

    if (source < 0) {
        perror("Unable to open vault file");
        return;
    }

    std::string outputPath =
        "retrieved_" + filename;

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

// --------------------------------------------------
// DELETE FILE
// --------------------------------------------------

void deleteFile() {

    std::string filename;

    std::cout << "\nEnter file name: ";
    std::cin >> filename;

    std::string path =
        VAULT_DIR + "/" + filename;

    if (unlink(path.c_str()) != 0) {
        perror("Unable to delete file");
        return;
    }

    std::cout << "File deleted successfully.\n";
}

// --------------------------------------------------
// MAIN
// --------------------------------------------------

int main() {

    createVault();

    if (!setupAuthentication()) {
        return 1;
    }

    if (!authenticate()) {
        return 1;
    }

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