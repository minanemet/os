/* Program ispisuje nazive svih fajlova unutar direktorijuma cija se
 * putanja proslednjuje kao argument komandne linije. Uz naziv fajla,
 * ispisati i ime vlasnika tog fajla u formatu:
 * <naziv_fajla> <ime_vlasnika>
 *
 * Primer poziva:
 * ./my_ls path
 */
#define _XOPEN_SOURCE 700
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>
#include <errno.h>
#include <string.h>

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
    // check argc

    DIR *dirstream = opendir(argv[1]);
    check_error(dirstream != NULL, "opendir");

    struct dirent *ent = NULL;

    errno = 0;
    while((ent = readdir(dirstream)) != NULL) {
        if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }
        char *filepath = malloc(strlen(argv[1]) + 1 + strlen(ent->d_name) + 1);
        // check malloc

        strcpy(filepath, argv[1]);
        strcat(filepath, "/");
        strcat(filepath, ent->d_name);

        struct stat file;
        stat(filepath, &file);
        // check stat

        struct passwd *owner = getpwuid(file.st_uid);
        // check getpwuid

        printf("-- %s  -- owner-> %s\n", ent->d_name, owner->pw_name);

        free(filepath);
        errno = 0;
    }

    check_error(errno == 0, "readdir");
    closedir(dirstream);
    
    exit(EXIT_SUCCESS);
}