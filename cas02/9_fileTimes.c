#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

/*
Napisati program koji ispisuje vreme pristupa, modifikacije
i poslednje promene statusa fajla. Dodatno, ispisati i trenutno vreme
na sistemu.

Poziv programa:
./fileinfo filePath
*/

#define check_error(cond,msg)\
    do {\
        if(!(cond)) {\
            perror(msg);\
            fprintf(stderr, "File: %s, Line: %d, Func: %s\n", __FILE__, __LINE__, __func__);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

int main(int argc, char **argv) {
    check_error(argc == 2, "./a.out filepath");

    errno = 0;
    struct stat fajl;
    stat(argv[1], &fajl);

    check_error(errno == 0, "stat");

    time_t vreme = time(NULL);
    check_error(vreme != (time_t)-1, "time");

    printf("Vreme pristupa: %s\nVreme modifikacije: %s\nVreme poslednje promene: %s\n\nVreme na sistemu:%s\n",
        ctime(&fajl.st_atim.tv_sec), 
        ctime(&fajl.st_mtim.tv_sec), 
        ctime(&fajl.st_ctim.tv_sec), 
        ctime(&vreme)
    );

}