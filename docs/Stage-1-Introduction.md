# Stage 1 – Project Introduction

## Project Title

Secure Linux File Manager & Kernel Audit System

## 1. Introduction

Secure Linux File Manager & Kernel Audit System is a C++ based Linux application designed to provide controlled file management while demonstrating Linux system programming and kernel-level interaction.

The application allows users to create, read, list, and delete files while demonstrating Linux file descriptors, file permissions, file locking, and communication between user space and the Linux kernel through a character device driver.

The project is implemented specifically for Linux using C++ and Linux system programming concepts.

## 2. Problem Statement

File operations performed directly through normal applications may not provide clear visibility into how files are accessed and managed at the system level.

The objective of this project is to develop a Linux-based file management system that demonstrates file operations using Linux system calls, controlled file access, file locking, and kernel-level audit communication.

## 3. Objectives

- Develop a Linux-based file management application using C++.
- Implement file creation, reading, listing, and deletion.
- Demonstrate Linux file descriptors and file operations.
- Use `open()`, `read()`, `write()`, and `close()`.
- Demonstrate file permissions and ownership information.
- Implement file locking.
- Generate audit events for file operations.
- Demonstrate user-space to kernel-space communication.
- Implement a Linux character device driver.
- Provide a simple command-line interface.

## 4. Project Scope

The project includes:

- File creation and storage.
- File reading.
- File listing.
- File deletion.
- File descriptor based I/O.
- Linux file permissions.
- File locking.
- Audit/event generation.
- Communication with a Linux character device driver.
- Kernel logging.
- Error handling and testing.

The project is designed as a software-only Linux application.

## 5. Expected Outcome

The expected system will provide the following operations:

1. Create and store a file.
2. Read a file.
3. List available files.
4. Delete a file.
5. View file permissions.
6. Modify file permissions.
7. Demonstrate file locking.
8. Generate audit events.
9. Communicate selected audit events to a character device driver.
10. Display kernel-level audit messages through Linux kernel logging.

## 6. Target Platform

- Operating System: Linux / Ubuntu
- Programming Language: C++
- Compiler: G++
- Build Tool: Make
- Development Environment: Visual Studio Code
- Version Control: Git
- Repository: GitHub

## 7. Future Improvements

Future improvements may include:

- Multi-user access management.
- More detailed permission management.
- Additional Linux system-call demonstrations.
- More detailed kernel auditing.
- Graphical user interface.
- Remote file-management capabilities.
