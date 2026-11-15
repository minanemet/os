/*
Napisati program koji cita n bajtova sa kraja fajla cija se putanja zadaje
kao argument komandne linije. Broj n se takodje zadaje kao argument komandne linije.
Procitani sadrzaj ispisati na standardni izlaz.

NAPOMENA: uraditi zadatak bez citanja pocetnog dela fajla (sadrzaj koji prethodi n-tom bajtu)

Poziv programa:
./read_bytes filepath n
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

int main(int argc, char **argv) {
    check_error(argc == 3, "./a.out filepath n");

    int n = atoi(argv[2]);

    int fd = open(argv[1], O_RDONLY);
    check_error(fd != -1, "open");

    check_error(lseek(fd, -n, SEEK_END) != -1, "lseek");

    char *buffer = malloc(n+1);
    int procitano = read(fd, buffer, n);
    check_error(procitano != -1, "read");

    buffer[procitano] = '\0';
    printf("%s\n", buffer);
    close(fd);
    free(buffer);

    exit(EXIT_SUCCESS);
}