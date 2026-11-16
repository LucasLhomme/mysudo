# 🛡️ MySudo — Privilege Escalation Tool in C

[![Language: C](https://img.shields.io/badge/Language-C-00599C.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build: Make](https://img.shields.io/badge/Build-Makefile-orange.svg)](Makefile)
[![Module: B-PSU-100](https://img.shields.io/badge/Epitech-B--PSU--100-blue.svg)](https://www.epitech.eu/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Academic Year: 2024-2025](https://img.shields.io/badge/Academic%20Year-2024--2025%20(Tek1)-blueviolet.svg)](#)

> **MySudo is a Unix privilege escalation utility in C**, replicating the core behavior of `sudo(8)` with user verification and credential elevation.

---

## ⚙️ Security Mechanics

- **Authentication:** Prompts user for their password and validates hashes via `crypt(3)` and `/etc/shadow`.
- **Privilege Transition:** Switches execution privileges to root (`UID 0`) or targeted user using `setuid(2)` and `setgid(2)`.
- **Process Execution:** Preserves sanitized environment and executes the requested command via `execvp(3)`.

---

## 🛠️ Build & Usage

```bash
make
./my_sudo whoami
# Output: root
```

---

## 📜 License

Licensed under the **MIT License with attribution** to Lucas Lhomme (Crabe).
