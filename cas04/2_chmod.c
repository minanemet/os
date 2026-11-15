/*
Napisati program koji fajlu cija se putanja zadaje
kao argument komandne linije ukida pravo citanja
za ostale i dodaje pravo pisanja za grupu.

Primedba:
- za ovakve operacije nad fajlom sam fajl ne otvaramo

Poziv programa:
./a.out filePath
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define check_error(cond, msg)                                                                     \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            perror(msg);                                                                           \
            fprintf(stderr, "File: %s\nFunction: %s\nLine: %d\n", __FILE__, __func__, __LINE__);   \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    } while (0)

int main(int argc, char **argv) {
    check_error(argc == 2, "./a.out filePath");

    struct stat file;
    
    check_error(stat(argv[1], &file) != -1, "stat");

    mode_t mods = (file.st_mode & ~S_IROTH) | S_IWGRP;

    check_error(chmod(argv[1], mods) != -1, "chmod");

    exit(EXIT_SUCCESS);
}