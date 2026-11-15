/* Program ispisuje nazive svih fajlova unutar trenutnog direktorijuma.
 * Podsetnik: relativna putanja do trenutnog direktorijuma je "."
 *
 * Napomena:
 * Za razliku od komande `ls` (bez opcije -a), ovde se ispisuju i skriveni fajlovi,
 * odnosno fajlovi čije ime počinje karakterom '.'.
 *
 * Skriveni fajlovi se u Unix/Linux sistemima koriste za čuvanje konfiguracionih
 * i sistemskih podataka (npr. .bashrc, .profile, .gitignore) i podrazumevano
 * nisu vidljivi kako ne bi zatrpavali korisnika uobičajenim izlazom komandi.
 *
 * Primer poziva:
 * ./my_ls
 */
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <dirent.h>
#include <errno.h>
#include <string.h>
//#define _XOPEN_SOURCE 700

#define check_error(cond, msg)                                                                     \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            perror(msg);                                                                           \
            fprintf(stderr, "File: %s\nFunction: %s\nLine: %d\n", __FILE__, __func__, __LINE__);   \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    } while (0)

int main(int argc, char **argv)
{
    check_error(argc == 1, "./a.out");

    DIR *dir = opendir(".");
    // check

    struct dirent *ent = NULL;

    errno = 0;
    while((ent = readdir(dir)) != NULL) {
        if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
            printf("-- %s\n", ent->d_name);
        }
    }

    closedir(dir);

    exit(EXIT_SUCCESS);
}