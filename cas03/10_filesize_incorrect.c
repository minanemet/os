/*
Napisati program koji ispisuje velicinu fajla koriscenjem
sistemskog poziva lseek.

Napomena:
- ovo je pogresan nacin za izracunavanje velicine fajla.
Da bi program radio, neophodno je pravo citanja nad
zadatim fajlom, sto ne bi trebalo da bude slucaj,
jer zapravo ne citamo sadrzaj fajla, već meta informacije
o njemu. Za velicinu fajla koristimo sistemski poziv stat.

Poziv programa:
./filesize filename

Domaci:
Umesto sa regularnim fajlom, probati sa standardnim izlazom (STDOUT_FILENO).
lseek ce puci. Zasto?
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#define check_error(cond,msg)\
    do {\
        if(!(cond)) {\
            perror(msg);\
            fprintf(stderr, "File: %s, line: %d, func %s\n", __FILE__, __LINE__, __func__);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

int main(int argc, char **argv) {
    check_error(argc == 2, "./a.out filepath");
    
    int fd = open(argv[1], O_RDONLY);
    check_error(fd != -1, "open");

    off_t filesize = lseek(fd, 0, SEEK_END);
    check_error(filesize >= 0, "lseek fail");

    close(fd);
    printf("Velicina fajla: %ld\n", (intmax_t)filesize);

    exit(EXIT_SUCCESS); 
}
