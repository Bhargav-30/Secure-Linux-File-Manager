# Stage 2 – Project Requirements & Development Plan

## 1. Project Overview

Secure Linux File Manager & Kernel Audit System is a command-line application developed using C++ on Linux. The system is designed to provide controlled file management while demonstrating Linux system programming and user-space to kernel-space communication.

## 2. Functional Requirements

### FR-01 File Creation and Storage

The system shall allow the user to create and store files.

### FR-02 File Reading

The system shall allow the user to read the contents of files.

### FR-03 File Listing

The system shall display the files available in the managed directory.

### FR-04 File Deletion

The system shall allow the user to delete files.

### FR-05 File Descriptor Management

The application shall demonstrate Linux file operations using:

- `open()`
- `read()`
- `write()`
- `close()`

### FR-06 File Permissions

The system shall display file permissions and ownership information and allow file permission modification where permitted.

### FR-07 File Locking

The system shall provide file locking to prevent conflicting file operations.

### FR-08 Kernel Audit Communication

The application shall communicate selected file-operation events to a Linux character device driver.

### FR-09 Kernel Logging

The character device driver shall receive audit events and record them using Linux kernel logging.

### FR-10 Error Handling

The system shall handle:

- Invalid user input.
- Missing files.
- Permission errors.
- File-locking failures.
- File-operation errors.
- System-call errors.

## 3. Non-Functional Requirements

### Security

The system shall use Linux file permissions and access-control mechanisms to control file access.

### Reliability

The application shall handle file-operation and system-call errors appropriately.

### Performance

The application shall avoid unnecessary processing and maintain reasonable performance for normal file operations.

### Usability

The application shall provide a simple command-line interface.

### Portability

The application shall be designed for standard Linux environments with a compatible C++ compiler.

### Maintainability

The application shall use modular C++ classes, organized source files, and clear documentation.

## 4. Major Modules

```text
Secure Linux File Manager
|
+-- CLI Module
|
+-- File Management Module
|
+-- File Descriptor Module
|
+-- Permission Management Module
|
+-- File Locking Module
|
+-- Audit/Event Module
|
+-- Linux Character Device Driver
```

### CLI Module

Responsibilities:

- Display the main menu.
- Accept user commands.
- Validate input.
- Display operation results and errors.

### File Management Module

Responsibilities:

- Create files.
- Read files.
- List files.
- Delete files.

### File Descriptor Module

Responsibilities:

- Demonstrate Linux file descriptors.
- Use `open()`, `read()`, `write()`, and `close()`.
- Handle file-descriptor errors.

### Permission Management Module

Responsibilities:

- Display file permissions.
- Display ownership information.
- Modify permissions where permitted.
- Handle permission errors.

### File Locking Module

Responsibilities:

- Acquire file locks.
- Release file locks.
- Prevent conflicting operations.
- Handle locking failures.

### Audit/Event Module

Responsibilities:

- Generate audit events.
- Record important file operations.
- Prepare audit information for kernel communication.

### Linux Character Device Driver

Responsibilities:

- Register the character device.
- Initialize the driver.
- Implement device `open()`, `read()`, and `write()` operations.
- Receive audit information from user space.
- Record events using kernel logging.
- Clean up the driver during removal.

## 5. Project Scope

### In Scope

- Linux file management.
- File creation.
- File reading.
- File listing.
- File deletion.
- Linux file descriptors and system calls.
- File permissions and ownership information.
- File locking.
- C++ object-oriented programming.
- Linux character device driver.
- User-space to kernel-space communication.
- Kernel logging.
- Error handling.
- Testing and documentation.

### Out of Scope

- Cloud storage.
- Web applications.
- Mobile applications.
- Network file sharing.
- Hardware-specific drivers.
- Distributed storage.
- Advanced cryptographic systems.

## 6. Key Features

- Command-line file management.
- Linux file descriptor based I/O.
- File permission management.
- File locking.
- File-operation monitoring.
- Audit/event generation.
- Character device driver interaction.
- Kernel logging.
- Error handling.

## 7. Deliverables

The project deliverables include:

- C++ source code.
- Linux-compatible application.
- Linux character device driver source.
- Makefiles and build instructions.
- README documentation.
- Stage-wise documentation.
- System architecture and diagrams.
- Test cases and results.
- Kernel log demonstration.
- GitHub repository and version history.

## 8. Development Plan

### Stage 1 – Project Introduction

Project definition, problem statement, objectives, scope, and expected outcome.

### Stage 2 – Requirements

Functional requirements, non-functional requirements, system modules, scope, features, and deliverables.

### Stage 3 – System Design

System architecture, data structures, class design, sequence diagrams, state model, and implementation plan.

### Stage 4 – Implementation

Implementation of the CLI, file manager, Linux file descriptor operations, permissions, file locking, audit logging, and character device driver.

### Stage 5 – Testing and Integration

Testing of file operations, permissions, file locking, audit logging, and user-space to kernel-space communication.

### Stage 6 – Finalization

Final implementation, documentation, GitHub repository preparation, and project demonstration.

## 9. Development Timeline

| Stage | Activity | Expected Output |
|------|----------|-----------------|
| Stage 1 | Project Introduction | Project definition |
| Stage 2 | Requirements | Functional and non-functional requirements |
| Stage 3 | System Design | Architecture and system design |
| Stage 4 | Implementation | Working Linux file manager |
| Stage 5 | Testing and Integration | Tested and integrated system |
| Stage 6 | Finalization | Final project and documentation |