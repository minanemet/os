/*
Napisati program koji ispisuje velicinu fajla na
standardni izlaz ukoliko ni vlasnik, ni grupa vlasnik,
a ni ostali nemaju pravo citanja.

Poziv programa:
./a.out <filepath>
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
    check_error(argc == 2, "./a.out filepath");
    
    struct stat file;
    int ret = stat(argv[1], &file);
    check_error(ret != -1, "stat");

    mode_t mod = file.st_mode;

    if(((mod & S_IRUSR) == 0) && ((mod & S_IRGRP) == 0) &&((mod & S_IROTH) == 0)) {
        printf("Velicina fajla: %ld\n", (intmax_t)file.st_size);
    }

    exit(EXIT_SUCCESS); 
}
