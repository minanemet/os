/* Program rekurzivno izdvaja sve fajlove koji su modifikovani
 * u poslednjih n dana u direktorijumu na putanji koju prosledi korisnik
 *
 * Primer poziva:
 * ./filterByTime dirPath days
 */
#define _XOPEN_SOURCE 700
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

#define check_error(cond, msg)                                                                     \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            perror(msg);                                                                           \
            fprintf(stderr, "File: %s\nFunction: %s\nLine: %d\n", __FILE__, __func__, __LINE__);   \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    } while (0)

#define DAY_IN_SEC (24 * 60 * 60)

int days = 0;

int filterByTime(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{   
    //UNUSED(typeflag);
    //UNUSED(ftwbuf);

    time_t sad = time(NULL);
    time_t razlika = sad - sb->st_mtim.tv_sec;
    
    if(razlika / DAY_IN_SEC < days) {
        printf("%s\n", fpath);
    }

    // return 0 important!
    return 0;
}

int main(int argc, char **argv)
{
    check_error(argc == 3, "./filterExt path days");

    /* prebacivanje stringa u broj */
    days = atoi(argv[2]);

    struct stat fInfo;
    check_error(stat(argv[1], &fInfo) != -1, "stat failed");
    check_error(S_ISDIR(fInfo.st_mode), "not a dir");

    check_error(nftw(argv[1], filterByTime, 50, 0) != -1, "nftw failed");

    exit(EXIT_SUCCESS);
}