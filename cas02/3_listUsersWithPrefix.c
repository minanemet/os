#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>

#define check_error(cond, msg)\
    do {\
        if(!(cond)) {\
            perror(msg);\
            fprintf(stderr, "File: %s\nFunction: %s\nLine: %d\n", __FILE__, __func__, __LINE__);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

int check_prefix(char *prefix, char *name) {
    while(*prefix != '\0') {
        if(*prefix != *name) {
            return 0;
        }

        prefix++;
        name++;
    }

    return 1;
}

char *dir_name(char *dir) {
    if(strcmp(dir, "/") == 0) {
        return dir;
    }

    char *last = strrchr(dir, '/');

    return (last == NULL) ? dir : last;
}

int main(int argc, char **argv) {
    check_error(argc == 2, "./a.out prefix");

    struct passwd *korisnik = NULL;

    setpwent();

    errno = 0;

    while((korisnik = getpwent()) != NULL) {
        if(check_prefix(argv[1], korisnik->pw_name)) {
            printf("Korisnik: %s, Putanja: %s\n", korisnik->pw_name, dir_name(korisnik->pw_dir));
        }

        errno = 0;
    }

    check_error(errno == 0, "getpwent");

    endpwent();

    exit(EXIT_SUCCESS);
}