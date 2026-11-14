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

int main(int argc, char **argv) {
    check_error(argc == 3, "./a.out user1 user2");

    errno = 0;
    struct passwd *user = getpwnam(argv[1]);
    check_error(user != NULL, "getpwnam");

    char *user1_dir = malloc(strlen(user->pw_dir) + 1);
    check_error(user1_dir != NULL, "malloc");

    strcpy(user1_dir, user->pw_dir);

    getpwnam(argv[2]);

    if(strcmp(user1_dir, user->pw_dir) == 0) {
        printf("Korisnici %s i %s imaju isti home direktorijum %s!\n", argv[1], argv[2], user->pw_dir);
    } else {
        printf("Korisnici %s i %s nemaju isti home direktorijum(%s, %s)\n", argv[1], argv[2], user1_dir, user->pw_dir);
    }

    free(user1_dir);

    exit(EXIT_SUCCESS);
}