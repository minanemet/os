/* Program kreira fajl pravima pristupa koja zeli korisnik.
 * U slucaju da fajl postoji, bice mu promenjena prava pristupa.
 *
 * Primer poziva:
 * ./umask_demo test.txt 777
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
    check_error(argc == 3, "./a.out fileName mode");

    errno = 0;

    int mods = strtol(argv[2], NULL, 8);
    int oldmask = umask(0);

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, mods);
    if(errno == EEXIST) {
        printf("Fajl vec postoji!\n");
        chmod(argv[1], mods);
    } 

    umask(oldmask);
    close(fd);

    exit(EXIT_SUCCESS);
}