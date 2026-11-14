#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <pwd.h>

#define check_error(cond, msg)\
    do {\
        if(!(cond)) {\
            perror(msg);\
            fprintf(stderr, "File :%s\nFunction: %s\nLine: %d\n", __FILE__, __func__, __LINE__);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

int main(int argc, char **argv) {
    check_error(argc == 2, "./a.out username");

    errno = 0;
    struct passwd *korisnik = getpwnam(argv[1]);

    if(korisnik == NULL) {
        if(errno == 0) {
            printf("Korisnik sa imenom %s ne postoji!\n", argv[1]);
        } else {
            check_error(0, "getpwnam greska");
        }
    } else {
        printf("Ime: %s\nPasswd: %s\n", korisnik->pw_name, korisnik->pw_passwd);
    }


    exit(EXIT_SUCCESS);
}