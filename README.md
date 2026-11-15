# Linux User & Group Management Cheat Sheet

A quick reference guide for inspecting and managing users, groups, and permissions on Linux systems.

---

## Users

List all local and network users:
```bash
getent passwd
```

List only usernames (first column):
```bash
getent passwd | cut -d: -f1
```

List human (non-system) users (UID >= 1000):
```bash
awk -F: '\$3 >= 1000 && \$1 != "nobody" {print \$1}' /etc/passwd
```

Get detailed info about a specific user (UID, GID, and groups):
```bash
id username
```

View user account expiration and password aging info:
```bash
chage -l username
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
*(Alternative using `getent`)*:
```bash
getent group | grep -w username
```

List all members of a specific group:
```bash
getent group groupname
```

---

## Active Sessions & Login History

See who is currently logged in and what they are running:
```bash
w
```

List currently logged-in users (short format):
```bash
who
```

View recent login history:
```bash
last -n 10
```

View the last login time for all users:
```bash
lastlog
```

---

## User & Group Modification (Requires `sudo`)

Create a new user with a home directory and default shell:
```bash
sudo useradd -m -s /bin/bash username
```

Set or change a user's password:
```bash
sudo passwd username
```

Add an existing user to a supplementary group (without removing existing groups):
```bash
sudo usermod -aG groupname username
```

Lock or unlock a user account:
```bash
sudo usermod -L username   # Lock
sudo usermod -U username   # Unlock
```

Delete a user and their home directory:
```bash
sudo userdel -r username
```

Create a new group:
```bash
sudo groupadd groupname
```

---

## Sudo & Privileges

Check what commands your current user can run with `sudo`:
```bash
sudo -l
```

Safely edit the `/etc/sudoers` file:
```bash
sudo visudo
```
