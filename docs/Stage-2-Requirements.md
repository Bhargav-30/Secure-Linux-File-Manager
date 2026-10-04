# Stage 2 – Project Requirements & Development Plan

## 1. Project Overview

Secure Linux File Vault is a command-line application developed using C++ on Linux. The system is designed to provide controlled and secure management of sensitive files.

## 2. Functional Requirements

The system shall provide the following functionality:

### FR-01: User Authentication
The system shall authenticate the user before allowing access to the vault.

### FR-02: Store File
The system shall allow an authenticated user to store files inside the secure vault.

### FR-03: Retrieve File
The system shall allow an authenticated user to retrieve files from the vault.

### FR-04: List Files
The system shall display files currently stored in the vault.

### FR-05: Delete File
The system shall allow an authenticated user to delete files from the vault.

### FR-06: File Encryption
Files stored in the vault shall be protected using encryption.

### FR-07: File Integrity Verification
The system shall verify whether a stored file has been modified without authorization.

### FR-08: Access Control
The system shall restrict vault operations to authorized users.

### FR-09: Audit Logging
The system shall maintain logs of important vault operations.

### FR-10: Error Handling
The system shall handle invalid input, missing files, authentication failures, and file-operation errors.

## 3. Non-Functional Requirements

### Security
Sensitive files and authentication information should not be stored in plain text.

### Reliability
The application should handle unexpected errors without corrupting stored files.

### Performance
File operations should complete with minimal unnecessary processing overhead.

### Usability
The command-line interface should be simple and easy to understand.

### Portability
The application should operate on standard Linux environments with the required C++ compiler.

### Maintainability
The source code should be modular, documented, and organized into appropriate components.

## 4. Major Modules

The project will be divided into the following modules:

```text
Secure Linux File Vault
│
├── Authentication Module
├── File Management Module
├── Encryption Module
├── Integrity Verification Module
├── Access Control Module
├── Audit Logging Module
└── Linux System Interface
```
## 5. Project Scope

### In Scope

- Secure storage of files in a protected vault.
- User authentication.
- File encryption and decryption.
- File integrity verification.
- Access control for vault operations.
- Audit logging of important activities.
- Linux file-system and system-level interaction.
- Command-line based operation.

### Out of Scope

- Cloud-based storage.
- Mobile application.
- Web-based interface.
- Distributed multi-server deployment.
- Enterprise-level authentication systems.

## 6. Key Features

- Password-based authentication.
- Secure file storage.
- File retrieval and deletion.
- File encryption and decryption.
- Integrity/tamper detection.
- Access control.
- Audit logging.
- Linux system-level file operations.
- Command-line interface.

## 7. Project Deliverables

The project will deliver:

- C++ source code.
- Linux-compatible application.
- Linux kernel-module/component implementation where applicable.
- Makefile and build instructions.
- Project README.md.
- Stage-wise documentation.
- Architecture and UML diagrams.
- Test cases and test results.
- GitHub repository with version history.

## 8. Development Plan

### Stage 1 – Project Introduction
- Define the project idea.
- Identify the problem.
- Define objectives, scope, and expected outcome.

### Stage 2 – Requirements
- Prepare functional and non-functional requirements.
- Define project modules and features.
- Prepare the Project Requirements Document.

### Stage 3 – System Design
- Design the overall architecture.
- Define module responsibilities and data structures.
- Prepare UML diagrams.
- Define the implementation approach.

### Stage 4 – Initial Implementation
- Develop the command-line interface.
- Implement basic file storage and retrieval.
- Integrate the core vault modules.
- Demonstrate the initial working prototype.

### Stage 5 – Testing and Improvement
- Implement security features.
- Perform unit and integration testing.
- Debug and improve the system.
- Measure and evaluate system behavior.

### Stage 6 – Final Implementation
- Complete the project.
- Finalize testing and documentation.
- Prepare GitHub repository.
- Demonstrate the complete system.

## 9. Development Timeline

| Stage | Activity | Planned Output |
|---|---|---|
| Stage 1 | Introduction | Project definition |
| Stage 2 | Requirements | PRD and requirements |
| Stage 3 | Design | Architecture and UML |
| Stage 4 | Prototype | Working basic vault |
| Stage 5 | Testing & Improvement | Tested and improved system |
| Stage 6 | Finalization | Final project and documentation |