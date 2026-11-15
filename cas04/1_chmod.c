/*
Program postavlja prava pristupa 'permissions' fajlu na putanji
'filePath'. Prava se zadaju u oktalnom formatu.

Poziv programa:
./a.out filePath permissions
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

#define check_error(cond, msg)                                                                     \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            perror(msg);                                                                           \
            fprintf(stderr, "File: %s\nFunction: %s\nLine: %d\n", __FILE__, __func__, __LINE__);   \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    } while (0)

int main(int argc, char **argv) {
    check_error(argc == 3, "./a.out filePath permissions");

    long int perms = strtol(argv[2], NULL, 8);
    check_error(chmod(argv[1], perms) != -1, "chmod");

    exit(EXIT_SUCCESS);
}