#include "FileManager.h"
#include "PermissionManager.h"
#include "FileLockManager.h"
#include "AuditLogger.h"

#include <iostream>
#include <string>
#include <vector>

int main() {

    const std::string dataPath = "data";
    const std::string logPath = "logs/audit.log";

    FileManager fileManager(dataPath);
    PermissionManager permissionManager;
    FileLockManager lockManager;
    AuditLogger auditLogger(logPath);

    int choice;

    while (true) {

        std::cout << "\n====================================\n";
        std::cout << " Secure Linux File Manager\n";
        std::cout << "====================================\n";
        std::cout << "1. Create File\n";
        std::cout << "2. Read File\n";
        std::cout << "3. List Files\n";
        std::cout << "4. Delete File\n";
        std::cout << "5. Show Permissions\n";
        std::cout << "6. Change Permissions\n";
        std::cout << "7. Lock File\n";
        std::cout << "8. Unlock File\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter choice: ";

        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {

            std::string filename;
            std::string content;

            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);

            std::cout << "Enter file content: ";
            std::getline(std::cin, content);

            if (fileManager.createFile(filename, content)) {

                std::cout << "File created successfully.\n";

                auditLogger.logEvent(
                    "CREATE",
                    filename,
                    "SUCCESS"
                );

            } else {

                std::cout << "File creation failed.\n";

                auditLogger.logEvent(
                    "CREATE",
                    filename,
                    "FAILED"
                );
            }
        }

        else if (choice == 2) {

    std::string filename;
    std::string content;

    std::cout << "Enter filename: ";
    std::getline(std::cin, filename);

    std::string path = dataPath + "/" + filename;

    if (lockManager.isLocked(path)) {

        std::cout
            << "File is currently locked. "
            << "Unlock it before reading.\n";

        auditLogger.logEvent(
            "READ",
            filename,
            "FAILED_LOCKED"
        );

    } else if (fileManager.readFile(filename, content)) {

        std::cout << "\n----- File Content -----\n";
        std::cout << content << '\n';
        std::cout << "------------------------\n";

        auditLogger.logEvent(
            "READ",
            filename,
            "SUCCESS"
        );

    } else {

        std::cout << "File reading failed.\n";

        auditLogger.logEvent(
            "READ",
            filename,
            "FAILED"
        );
    }
}

        else if (choice == 3) {

            std::vector<std::string> files =
                fileManager.listFiles();

            std::cout << "\nFiles:\n";

            if (files.empty()) {

                std::cout << "No files found.\n";

            } else {

                for (const std::string& file : files) {
                    std::cout << "- " << file << '\n';
                }
            }

            auditLogger.logEvent(
                "LIST",
                dataPath,
                "SUCCESS"
            );
        }

        else if (choice == 4) {

            std::string filename;

            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);

            if (fileManager.deleteFile(filename)) {

                std::cout << "File deleted successfully.\n";

                auditLogger.logEvent(
                    "DELETE",
                    filename,
                    "SUCCESS"
                );

            } else {

                std::cout << "File deletion failed.\n";

                auditLogger.logEvent(
                    "DELETE",
                    filename,
                    "FAILED"
                );
            }
        }

        else if (choice == 5) {

            std::string filename;

            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);

            std::string path =
                dataPath + "/" + filename;

            if (permissionManager.showPermissions(path)) {

                auditLogger.logEvent(
                    "PERMISSION_VIEW",
                    filename,
                    "SUCCESS"
                );

            } else {

                auditLogger.logEvent(
                    "PERMISSION_VIEW",
                    filename,
                    "FAILED"
                );
            }
        }

        else if (choice == 6) {

            std::string filename;
            unsigned int mode;

            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);

            std::cout << "Enter permission mode (example 644): ";
            std::cin >> mode;
            std::cin.ignore();

            std::string path =
                dataPath + "/" + filename;

            if (permissionManager.changePermissions(path, mode)) {

                std::cout << "Permissions changed successfully.\n";

                auditLogger.logEvent(
                    "PERMISSION_CHANGE",
                    filename,
                    "SUCCESS"
                );

            } else {

                std::cout << "Permission change failed.\n";

                auditLogger.logEvent(
                    "PERMISSION_CHANGE",
                    filename,
                    "FAILED"
                );
            }
        }

        else if (choice == 7) {

            std::string filename;

            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);

            std::string path =
                dataPath + "/" + filename;

            if (lockManager.lockFile(path)) {

                std::cout << "File locked successfully.\n";

                auditLogger.logEvent(
                    "LOCK",
                    filename,
                    "SUCCESS"
                );

            } else {

                std::cout << "File locking failed.\n";

                auditLogger.logEvent(
                    "LOCK",
                    filename,
                    "FAILED"
                );
            }
        }

        else if (choice == 8) {

            std::string filename;

            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);

            std::string path =
                dataPath + "/" + filename;

            if (lockManager.unlockFile(path)) {

                std::cout << "File unlocked successfully.\n";

                auditLogger.logEvent(
                    "UNLOCK",
                    filename,
                    "SUCCESS"
                );

            } else {

                std::cout << "File unlocking failed.\n";

                auditLogger.logEvent(
                    "UNLOCK",
                    filename,
                    "FAILED"
                );
            }
        }

        else if (choice == 9) {

            std::cout << "Exiting application.\n";
            break;
        }

        else {

            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
