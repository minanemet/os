#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

/*
Ispisati velicinu fajla na standardni izlaz. Putanja do fajla
se prosledjuje kao argument komandne linije.

Poziv programa:
./fileinfo filePath
*/

#define check_error(cond, msg)\
 do {\
    if(!(cond)){\
        perror(msg);\
        fprintf(stderr, "File: %s, Function: %s, Line: %d\n", __FILE__, __func__, __LINE__);\
        exit(EXIT_FAILURE);\
    }\
 } while (0)

 int main(int argc, char **argv) {
    check_error(argc == 2, "./a.out filepath");

    struct stat fileinfo;
    check_error(stat(argv[1], &fileinfo) != -1, "stat");

    printf("Velicina fajla je %ld\n", (intmax_t)fileinfo.st_size);

    exit(EXIT_SUCCESS);
 }