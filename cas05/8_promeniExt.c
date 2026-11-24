/*
Poziv programa;
./a.out path ext

Program dodaje ekstenziju 'ext' na ime fajla koji se nalazi
na putanji 'path'. Iako bi rename sistemski poziv
bio ispravniji izbor ovde, ovaj primer koristimo za vezbanje.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define check_error(cond, msg)\
    do {\
        if(!(cond)) {\
            perror(msg);\
            fprintf(stderr, "File: %s, line: %d, func: %s\n", __FILE__, __LINE__, __func__);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

char *izmeni_ext(char *staro_ime, char *ext) {
    char *posl = strrchr(staro_ime, '.');
    int posll = posl - staro_ime + 1;
    int extl = strlen(ext);
    char *novo = malloc(posll + extl + 1);

    strncpy(novo, staro_ime, posll);
    strcat(novo, ext);

    return novo;
}

int main(int argc, char** argv) {
    check_error(argc == 3, "./a.out path ext");

    int fd1 = open(argv[1], O_RDONLY);
    char *novo_ime = izmeni_ext(argv[1], argv[2]);

    struct stat fileInfo;
    check_error(stat(argv[1], &fileInfo) != -1, "stat");

    mode_t mask = umask(0);
    
    int fd2 = open(novo_ime, O_WRONLY | O_CREAT | O_TRUNC, fileInfo.st_mode);

    umask(mask);

    char *buffer = malloc(1024);
    int procitano;
    while((procitano = read(fd1, buffer, 1024)) > 0) {
        check_error(write(fd2, buffer, procitano) == procitano, "write");
    }

    check_error(procitano != -1, "read");

    unlink(argv[1]);

    free(buffer);
    free(novo_ime);
    close(fd1);
    close(fd2);

    exit(EXIT_SUCCESS);
}