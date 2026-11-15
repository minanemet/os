/* Ispisati ukupnu velicinu direktorijuma cija se putanja zadaje kao
 * argument komandne linije.
 *
 * Primer poziva:
 * ./filterByTime dirpath
 */
#define _XOPEN_SOURCE 700
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define UNUSED(x) ((void)x)

#define check_error(cond, msg)                                                                     \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            perror(msg);                                                                           \
            fprintf(stderr, "File: %s\nFunction: %s\nLine: %d\n", __FILE__, __func__, __LINE__);   \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    } while (0)

long int total = 0;

int calculate_size(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    UNUSED(fpath);
    UNUSED(typeflag);
    UNUSED(ftwbuf);

    total += sb->st_size;

    return 0;
}

int main(int argc, char **argv)
{
    check_error(argc == 2, "./filterExt path ");

    // provera da li se radi o direktorijumu
    struct stat fajl;
    stat(argv[1], &fajl);
    // check
    
    check_error(S_ISDIR(fajl.st_mode), "not a dir");

    check_error(nftw(argv[1], calculate_size, 50, 0) != -1, "nftw");

    printf("Velicina direktorijuma je %ld\n", total);
    exit(EXIT_SUCCESS);
}