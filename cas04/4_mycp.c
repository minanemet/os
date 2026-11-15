/*
Napisati program koji kopira fajl sa jedne lokacije na drugu.

Poziv programa:
./a.out destPath srcPath
*/
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define check_error(cond, msg)                                                                     \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            perror(msg);                                                                           \
            fprintf(stderr, "File: %s\nFunction: %s\nLine: %d\n", __FILE__, __func__, __LINE__);   \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    } while (0)

#define BUFFER_SIZE 4096

int main(int argc, char **argv) 
{
    check_error(argc == 3, "./a.out dest src");

    int fdSrc = open(argv[2], O_RDONLY);
    check_error(fdSrc != -1, "open 1");

    int fdDest = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    check_error(fdDest != -1, "open 2");

    char *buffer = malloc(BUFFER_SIZE);

    int procitano;
    while((procitano = read(fdSrc, buffer, BUFFER_SIZE)) > 0) {
        int upisano = write(fdDest, buffer, procitano);
        check_error(upisano == procitano, "write");
    }
    check_error(procitano != -1, "read");

    struct stat file;
    check_error(stat(argv[2], &file) != -1, "stat");

    check_error(chmod(argv[1], file.st_mode) != -1, "chmod");

    free(buffer);
    close(fdSrc);
    close(fdDest);

    exit(EXIT_SUCCESS);
}