/*
Napisati program koji ispisuje sadrzaj prosledjenog fajla
na standardni izlaz koriscenjem sistemskih poziva read i write.

Poziv programa:
./os_cat filename
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#define check_error(cond,msg)\
    do {\
        if(!(cond)) {\
            perror(msg);\
            fprintf(stderr, "File: %s, line: %d, func %s\n", __FILE__, __LINE__, __func__);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    check_error(argc == 2, "./a.out filename");

    int fd = open(argv[1], O_RDONLY);
    check_error(fd != -1, "open");

    char *buffer = malloc(BUFFER_SIZE);
    check_error(buffer != NULL, "malloc");

    int procitano;

    while((procitano = read(fd, buffer, BUFFER_SIZE)) > 0) {
        check_error((write(STDOUT_FILENO, buffer, procitano) == procitano), "write");
    }

    free(buffer);
    close(fd);

    exit(EXIT_SUCCESS);
}