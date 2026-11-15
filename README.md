# Linux User & Group Management Cheat Sheet

A quick reference guide for inspecting and managing users, groups, and permissions on Linux systems.

---

## Users

C functions:
```bash
getpwent,  setpwent,  endpwent - get password file entry
getpwnam,  getpwnam_r,  getpwuid, getpwuid_r - get password file entry
```

List all local and network users:
```bash
getent passwd
```

Get detailed info about a specific user (UID, GID, and groups):
```bash
id username
```

---

## Groups

List all local and network groups:
```bash
getent group
```

List all groups a specific user belongs to:
```bash
groups username
```

List all members of a specific group:
```bash
getent group groupname
```