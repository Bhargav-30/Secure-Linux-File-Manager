# Stage 3 – System Design & Architecture

## 1. System Architecture

The Secure Linux File Vault follows a modular layered architecture.

```text
                                        USER
                                         |
                                         v
                                +-------------------+
                                |   CLI Interface   |
                                +---------+---------+
                                          |
                              +-----------+-----------+
                              |           |           |
                              v           v           v
                       Authentication   File      Access Control
                           Module       Manager
                              |           |
                              +-----------+-----------+
                                          |
                                          v
                                 +----------------+
                                 | Security Layer |
                                 +-------+--------+
                                         |
                              +----------+----------+
                              |                     |
                              v                     v
                        Encryption Module    Integrity Module
                              |                     |
                              +----------+----------+
                                         |
                                         v
                                 Linux File System
                                    /         \
                                   v           v
                            Vault Files     Audit Logs


                            C++ Application
                                   |
                                   v
                          Linux Device Driver
                                   |
                                   v
                             Linux Kernel
```

## 2. System Components and Responsibilities
## 2.1 CLI Interface
Provides a command-line interface for the user to interact with the vault.
Responsibilities:
- Display the main menu.
- Accept user input.
- Validate commands.
- Display operation results.
## 2.2 Authentication Module
Responsible for verifying the identity of the user before allowing protected operations.
Responsibilities:
- Accept user credentials.
- Verify credentials.
- Handle authentication failures.
- Maintain authentication status.
## 2.3 File Management Module
Handles basic vault file operations.
Responsibilities:
- Store files.
- Retrieve files.
- List files.
- Delete files.
- Perform Linux file operations.
## 2.4 Encryption Module
Protects the contents of files stored in the vault.
Responsibilities:
- Encrypt files before storage.
- Decrypt files during authorized retrieval.
- Handle encryption errors.
## 2.5 Integrity Verification Module
Detects unauthorized modification of stored files.
Responsibilities:
- Generate file integrity information.
- Store integrity information.
- Verify file integrity.
- Report integrity violations.
## 2.6 Access Control Module
Ensures that only authenticated users can perform protected operations.
Responsibilities:
- Check authentication status.
- Validate requested operations.
- Prevent unauthorized operations.
## 2.7 Audit Logging Module
Records important events such as:
- Successful login.
- Failed login.
- File storage.
- File retrieval.
- File deletion.
- Integrity violations.
## 2.8 Linux Device Driver Interface
Provides communication between the C++ application and a Linux kernel module.
The driver component will be used to demonstrate user-space and kernel-space interaction and will expose basic vault-related status or event information.
## 3. Data Structures
### User
```text
User
├── username
├── authentication status
└── access level
```

### VaultFile
```text
VaultFile
├── filename
├── stored path
├── file size
└── integrity information
```
### AuditRecord
```text
AuditRecord
├── timestamp
├── operation
├── filename
└── status
```
## 4. Class Diagram
```text
+----------------------+
|     AuthManager      |
+----------------------+
| - authenticated      |
| - username           |
+----------------------+
| + login()            |
| + logout()           |
| + isAuthenticated()  |
+----------------------+

+----------------------+
|    VaultManager      |
+----------------------+
| - vaultPath          |
+----------------------+
| + storeFile()        |
| + retrieveFile()     |
| + listFiles()        |
| + deleteFile()       |
+----------------------+

+----------------------+
|    CryptoManager     |
+----------------------+
| + encryptFile()      |
| + decryptFile()      |
+----------------------+

+----------------------+
|  IntegrityManager    |
+----------------------+
| + generateHash()     |
| + verifyIntegrity()  |
+----------------------+

+----------------------+
|     AuditLogger      |
+----------------------+
| + logEvent()         |
| + viewLogs()         |
+----------------------+
```

## 5. File Storage Sequence Diagram
```text
User
 |
 | Select Store File
 v
CLI
 |
 | Authenticate
 v
AuthManager
 |
 | Authentication successful
 v
VaultManager
 |
 | Encrypt file
 v
CryptoManager
 |
 | Generate integrity information
 v
IntegrityManager
 |
 | Store file
 v
Linux File System
 |
 v
AuditLogger
 |
 v
Success
```

## 6. File Retrieval Sequence Diagram
```text
User
 |
 | Select Retrieve File
 v
CLI
 |
 | Authenticate
 v
AuthManager
 |
 | Authentication successful
 v
VaultManager
 |
 | Verify integrity
 v
IntegrityManager
 |
 | Integrity valid
 v
CryptoManager
 |
 | Decrypt file
 v
Output File
 |
 v
AuditLogger
```
## 7. State Machine Diagram
```text
        +-------+
        | START |
        +---+---+
            |
            v
        +-------+
        | LOGIN |
        +---+---+
            |
       +----+----+
       |         |
     Failed    Success
       |         |
       v         v
    ACCESS     VAULT
    DENIED     ACTIVE
                 |
                 v
             OPERATION
                 |
          +------+------+
          |      |      |
        Store  Retrieve Delete
          |      |      |
          +------+------+
                 |
                 v
              LOGGING
                 |
                 v
                EXIT
```

## 8. Implementation Plan
The implementation will be completed incrementally:
1. Develop the command-line interface.
2. Implement basic file storage and retrieval.
3. Implement authentication.
4. Implement encryption and decryption.
5. Implement integrity verification.
6. Implement access control.
7. Implement audit logging.
8. Implement the Linux kernel/device-driver component.
9. Integrate and test all modules.
10. Finalize documentation and GitHub repository.
## 9. Development Environment and Tools
- Operating System: Linux
- Programming Language: C++
- Compiler: G++
- IDE: Visual Studio Code
- Version Control: Git
- Repository: GitHub
- Build Tool: Make
## 10. Git Repository and Version Control
Git will be used to maintain project history and track development progress.
Major development milestones will be committed separately, including:
- Initial project structure
- Stage 1 documentation
- Stage 2 requirements
- Stage 3 system design
- Initial implementation
- Security implementation
- Testing and improvements
- Final implementation