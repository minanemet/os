/*
Napisati program koji brise regularni fajl ili direktorijum,
pri cemu je dozvoljeno koristiti samo sistemske pozive.

Napomena:
- funkcija remove() je funkcija standardne C biblioteke
koja radi slicnu stvar, tj. sama proverava da li je prosledjeni
fajl regularan ili direktorijum.

Poziv programa:
./rmfile -[fd] path/to/file/or/directory
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
    check_error(argc == 3, "./a.out -[fd] filepath");

    check_error('-' == argv[1][0], "option");

    if('f' == argv[1][1]) {
        check_error(unlink(argv[2]) != -1, "unlink");
    } else if ('d' == argv[1][1]) {
        check_error(rmdir(argv[2]) != -1, "rmdir");
    } else {
        check_error(false, "option does not exist");
    }

    exit(EXIT_SUCCESS); 
}