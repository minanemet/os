/*
Napisati program koji cita n bajtova iz fajla cija se putanja zadaje
kao argument komandne linije. Broj n se takodje zadaje kao argument komandne linije.
Procitani sadrzaj ispisati na standardni izlaz.

Poziv programa:
./read_bytes filepath n
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

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

    int bytes = atoi(argv[2]);
    int fd = open(argv[1], O_RDONLY);
    check_error(fd != -1, "open");

    char *buffer = malloc(bytes + 1);
    check_error(buffer != NULL, "malloc");
    
    int procitano = read(fd, buffer, bytes);
    check_error(procitano != -1, "read");

    buffer[procitano] = '\n';
    printf("%s\n", buffer);

    close(fd);
    free(buffer);

    exit(EXIT_SUCCESS); 
}