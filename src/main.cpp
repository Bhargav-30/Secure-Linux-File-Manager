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

#include "crypto.h"

namespace fs = std::filesystem;

const std::string VAULT_DIR = "vault";
const std::string AUTH_FILE = "config/auth.dat";

std::string currentPassword;

// --------------------------------------------------
// PASSWORD HASH
// --------------------------------------------------

#include <openssl/sha.h>

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

    tcsetattr(
        STDIN_FILENO,
        TCSANOW,
        &newSettings
    );

    std::string password;

    std::getline(std::cin, password);

    tcsetattr(
        STDIN_FILENO,
        TCSANOW,
        &oldSettings
    );

    std::cout << '\n';

    return password;
}

// --------------------------------------------------
// CREATE VAULT
// --------------------------------------------------

void createVault() {

    fs::create_directories(VAULT_DIR);
    fs::create_directories("config");

    chmod(VAULT_DIR.c_str(), 0700);
}

// --------------------------------------------------
// PASSWORD SETUP
// --------------------------------------------------

bool setupAuthentication() {

    if (fs::exists(AUTH_FILE)) {
        return true;
    }

    std::cout << "\n====================================\n";
    std::cout << "          FIRST TIME SETUP\n";
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
// AUTHENTICATION
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

        if (hashPassword(password) == storedHash) {

            currentPassword = password;

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
// STORE ENCRYPTED FILE
// --------------------------------------------------

void storeFile() {

    std::string filename;

    std::cout << "\nEnter file path: ";
    std::cin >> filename;

    if (!fs::exists(filename)) {
        std::cout << "File not found.\n";
        return;
    }

    std::string safeName =
        fs::path(filename).filename().string();

    // Store the encrypted version with .enc extension
    std::string destination =
        VAULT_DIR + "/" + safeName + ".enc";

    if (encryptFile(
            filename,
            destination,
            currentPassword)) {

        chmod(destination.c_str(), 0600);

        std::cout << "File encrypted and stored successfully.\n";

    } else {

        std::cout << "Encryption failed.\n";
    }
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
// RETRIEVE AND DECRYPT
// --------------------------------------------------

void retrieveFile() {

    std::string filename;

    std::cout << "\nEnter stored file name: ";
    std::cin >> filename;

    std::string sourcePath =
        VAULT_DIR + "/" + filename;

    if (!fs::exists(sourcePath)) {

        std::cout << "File not found in vault.\n";
        return;
    }

    std::string outputPath =
        "retrieved_" + filename;

    if (outputPath.size() >= 4 &&
        outputPath.substr(
            outputPath.size() - 4
        ) == ".enc") {

        outputPath =
            outputPath.substr(
                0,
                outputPath.size() - 4
            );
    }

    if (decryptFile(
            sourcePath,
            outputPath,
            currentPassword)) {

        chmod(outputPath.c_str(), 0600);

        std::cout << "File decrypted successfully.\n";
        std::cout << "Output: "
                  << outputPath
                  << '\n';

    } else {

        std::cout << "Decryption failed.\n";
        std::cout << "Incorrect password or damaged file.\n";
    }
}

// --------------------------------------------------
// DELETE FILE
// --------------------------------------------------

void deleteFile() {

    std::string filename;

    std::cout << "\nEnter stored file name: ";
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