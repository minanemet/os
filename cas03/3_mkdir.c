/*
Napisati program koji kreira direktorijum sa imenom
koje se zadaje kao argument komandne linije, pri cemu
za prava pristupa tom direktorijimu koristiti 0755.

Poziv programa:
./a.out dir_name
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
    check_error(argc == 3, "./a.out filename");

    mode_t mode= strtol(argv[2], NULL, 8);

    check_error(mkdir(argv[1], mode) != -1, "mkdir");

    printf("Uspesno kreiran direktorijum %s\n", argv[1]);

    exit(EXIT_SUCCESS); 
}
