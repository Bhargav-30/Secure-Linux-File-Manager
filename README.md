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
```

## 6. How to Build the C++ Application

Open Ubuntu or WSL and move to the project directory:

```bash
cd ~/Secure-Linux-File-Vault
```

Build the application:

```bash
make
```

Run the application:

```bash
./filemanager
```

## 7. Application Menu

The application provides the following operations:

```text
====================================
 Secure Linux File Manager
====================================
1. Create File
2. Read File
3. List Files
4. Delete File
5. Show Permissions
6. Change Permissions
7. Lock File
8. Unlock File
9. Exit
```

## 8. File Management Operations

### Create File

The application allows the user to create a file and write content to it.

### Read File

The application reads file contents using Linux file operations.

### List Files

The application displays files available in the managed directory.

### Delete File

The application removes selected files.

## 9. Linux File Descriptor Operations

The project demonstrates Linux file descriptor based I/O using:

- `open()`
- `read()`
- `write()`
- `close()`

File descriptors are used to communicate with files at the operating-system level.

## 10. File Permissions

The project demonstrates Linux file permission management.

The application can:

- Display file permissions.
- Display file ownership information.
- Change file permissions where permitted.

Example permission mode:

```text
600
644
755
```

## 11. File Locking

The project implements file locking to provide controlled access to files.

The locking module supports:

- Acquiring a file lock.
- Releasing a file lock.
- Detecting locking failures.
- Preventing conflicting access from the application.

## 12. Audit Logging

Important file-management operations are recorded in:

```text
logs/audit.log
```

Example:

```text
2026-10-05 13:30:00 | CREATE | test.txt | SUCCESS
2026-10-05 13:30:10 | READ | test.txt | SUCCESS
2026-10-05 13:30:20 | PERMISSION_VIEW | test.txt | SUCCESS
2026-10-05 13:30:30 | LOCK | test.txt | SUCCESS
2026-10-05 13:30:40 | UNLOCK | test.txt | SUCCESS
```

The audit system records both successful and failed operations.

## 13. Character Device Driver

The project contains a Linux character device driver:

```text
driver/slf_audit.c
```

The driver is designed to demonstrate:

- Linux kernel module development.
- Character device registration.
- Device `open()` operation.
- Device `read()` operation.
- Device `write()` operation.
- User-space and kernel-space interaction.
- Kernel logging.
- Mutex-based synchronization.
- `copy_from_user()`.
- `copy_to_user()`.

The intended device name is:

```text
/dev/slf_audit
```

## 14. User-Space and Kernel-Space Architecture

```text
C++ File Manager
       |
       v
Audit / Event Module
       |
       v
/dev/slf_audit
       |
       v
Linux Character Device Driver
       |
       v
Linux Kernel
       |
       v
Kernel Log
```

## 15. Linux Concepts Demonstrated

The project demonstrates the following Linux and C++ concepts:

- User space and kernel space.
- File descriptors.
- Linux system calls.
- `open()`.
- `read()`.
- `write()`.
- `close()`.
- File permissions.
- File locking.
- Kernel modules.
- Character devices.
- User-space to kernel-space communication.
- Kernel logging.
- Mutex synchronization.
- Error handling.
- C++ object-oriented programming.
- Makefiles.
- Git version control.

## 16. C++ Design

The application is divided into separate C++ classes according to their responsibilities.

### FileManager

Responsible for:

- File creation.
- File reading.
- File listing.
- File deletion.

### PermissionManager

Responsible for:

- Viewing permissions.
- Changing permissions.

### FileLockManager

Responsible for:

- Locking files.
- Unlocking files.

### AuditLogger

Responsible for:

- Creating audit events.
- Recording file-management events.

### DriverInterface

The planned driver interface is responsible for communication between the user-space application and the Linux character device.

## 17. Build and Run Commands

### Build the application

```bash
make
```

### Run the application

```bash
./filemanager
```

### Clean build files

```bash
make clean
```

## 18. Character Driver Build

Go to the driver directory:

```bash
cd driver
```

Build the driver:

```bash
make
```

This produces the kernel module:

```text
slf_audit.ko
```

The module can be inspected using:

```bash
modinfo ./slf_audit.ko
```

## 19. Loading the Driver

On a Linux system with a matching kernel build environment:

```bash
sudo insmod slf_audit.ko
```

Check whether the module is loaded:

```bash
lsmod | grep slf_audit
```

Check the device:

```bash
ls -l /dev/slf_audit
```

Kernel messages can be inspected using:

```bash
sudo dmesg | tail
```

## 20. Kernel Driver Testing Note

The Linux character device driver is implemented as an external kernel module using Linux character-device APIs.

The driver successfully compiled against the Microsoft WSL 6.18.40.1 kernel source and produced the `slf_audit.ko` module.

During runtime testing on the stock WSL kernel, module insertion was rejected with:

```text
.gnu.linkonce.this_module section size must match
the kernel's built struct module size at run time
```

This indicates that the running WSL kernel and the available kernel build tree are not binary-identical even though their reported kernel release and module version information match.

The driver source is therefore included as part of the project and is intended to be loaded on a Linux environment with a matching kernel build tree.

## 21. Development Stages

### Stage 1 – Project Introduction

Project definition, problem statement, objectives, scope, and expected outcome.

### Stage 2 – Project Requirements

Functional requirements, non-functional requirements, system modules, features, project scope, and deliverables.

### Stage 3 – System Design

System architecture, data structures, C++ class design, sequence diagrams, state model, and implementation plan.

### Stage 4 – Implementation

Implementation of the C++ file manager, Linux file operations, permissions, file locking, audit logging, and character device driver.

### Stage 5 – Testing and Integration

Testing of file operations, permissions, locking, audit logging, and kernel-driver integration.

### Stage 6 – Finalization

Final implementation, documentation, GitHub repository preparation, and project demonstration.

## 22. Expected Project Output

The final system provides:

1. A Linux-based C++ file manager.
2. File creation, reading, listing, and deletion.
3. Linux file descriptor based operations.
4. File permission management.
5. File locking.
6. Audit logging.
7. Linux character device driver source.
8. User-space and kernel-space communication design.
9. Kernel logging support.
10. Complete project documentation.

## 23. Author

**Bhargav Raj**

BTech Computer Science and Engineering

## 24. Repository

GitHub Repository:

https://github.com/Bhargav-30/Secure-Linux-File-Manager
