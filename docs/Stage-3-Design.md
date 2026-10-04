# Stage 3 – System Design & Architecture

## 1. System Architecture

The Secure Linux File Vault follows a modular layered architecture.

```text
                    USER
                     |
                     v
            +-------------------+
            |   CLI Interface   |
            |     main.cpp      |
            +---------+---------+
                      |
          +-----------+-----------+
          |           |           |
          v           v           v
     Authentication  File      Access
       Module       Manager    Control
          |           |           |
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
                     |
             +-------+-------+
             |               |
             v               v
        Vault Files      Audit Logs