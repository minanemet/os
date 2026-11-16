# Linux Cheet Sheet

A quick reference guide for Linux man page info

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
## Time 
C functions:
```bash
utime,  utimes - change file last access and modification times
```
