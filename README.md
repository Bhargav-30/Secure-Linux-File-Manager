# Secure Linux File Manager & Kernel Audit System

## 1. Project Overview

Secure Linux File Manager & Kernel Audit System is a C++ based Linux command-line application developed to demonstrate Linux system programming and Linux device driver concepts.

The project provides file management operations and records important file events. Selected audit events are designed to communicate with a Linux character device driver and can be recorded through Linux kernel logging.

## 2. Objectives

- Implement a Linux-based file manager using C++.
- Demonstrate Linux file descriptors and system calls.
- Implement file creation, reading, listing, and deletion.
- Demonstrate file permissions.
- Implement file locking.
- Generate audit events for file operations.
- Demonstrate user-space to kernel-space communication.
- Implement a Linux character device driver.
- Provide a simple command-line interface.

## 3. Features

- Create file
- Read file
- List files
- Delete file
- View file permissions
- Change file permissions
- Lock file
- Unlock file
- User-space audit logging
- Linux character device driver source
- Kernel logging support
- Error handling

## 4. Technologies Used

- C++
- Linux / Ubuntu
- G++
- GNU Make
- Linux system calls
- Linux Kernel Modules
- Linux Character Device Driver
- Git
- GitHub
- Visual Studio Code

## 5. Project Structure

```text
Secure-Linux-File-Vault/
├── src/
│   ├── main.cpp
│   ├── FileManager.cpp
│   ├── PermissionManager.cpp
│   ├── FileLockManager.cpp
│   └── AuditLogger.cpp
│
├── include/
│   ├── FileManager.h
│   ├── PermissionManager.h
│   ├── FileLockManager.h
│   └── AuditLogger.h
│
├── driver/
│   ├── slf_audit.c
│   └── Makefile
│
├── tests/
├── logs/
├── docs/
│   ├── Stage-1-Introduction.md
│   ├── Stage-2-Requirements.md
│   └── Stage-3-System-Design.md
│
├── Makefile
├── README.md
└── .gitignore