/*
Napisati program koji zadati string upisuje u fajl koriscenjem sistemskog poziva write.
Putanja do fajla kao i zadati string se zadaju kao argumenti komandne linije.
Ukoliko zadati fajl ne postoji kreirati ga, a ukoliko postoji pre pisanja mu obrisati sadrzaj.

Poziv programa:
./write_bytes filepath some_text
./write_bytes 1.txt "ovo je neki tekst"
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

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
    
    char *str = argv[2];
    int len = strlen(str);
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0755);
    check_error(fd != -1, "open");

    int upisano = write(fd, str, len);
    check_error(upisano != -1, "write");

    close(fd);

    exit(EXIT_SUCCESS); 
}