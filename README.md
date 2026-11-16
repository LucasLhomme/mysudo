# MySudo

> **Privilege escalation utility in C.**

## Overview
Reimplementation of `sudo`:
- Validates user identity and password against shadow authentication
- Checks execution permissions and runs target commands under elevated UID/GID using `setuid`, `setgid`, and `execvp`

## Build & Usage
```bash
make
./my_sudo whoami
```

## License
Open-source under MIT License.
