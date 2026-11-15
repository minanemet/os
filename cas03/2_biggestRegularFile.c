/*
Kao argumenti komandne linije prosledjuju se fajlovi (razlicitih tipova).
Ispisati velicinu najveceg regularnog fajla od prosledjenih.

Pretpostaviti da nijedan fajl nece biti simbolicki link i da ce biti
prosledjen barem jedan regularan fajl.

Poziv programa:
./a.out <file1> <file2> ... <filen>
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define check_error(cond,msg)\
    do {\
        if(!(cond)) {\
            perror(msg);\
            fprintf(stderr, "File: %s, line: %d, func %s\n", __FILE__, __LINE__, __func__);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

int main(int argc, char **argv) {
    check_error(argc >= 2, "./a.out <file1> <file2> <file3> ...");
    
    off_t maxsize = 0;
    int max = 1;
    struct stat current;

    for(int i = 1; i < argc; i++) {
        check_error(stat(argv[i], &current) != -1, "stat");

        if(S_ISREG(current.st_mode) && current.st_size > maxsize) {
            maxsize = current.st_size;
            max = i;
        }
    }

    printf("Najveci regularni fajl je: %s, velicina: %ld\n", argv[max], maxsize);

    exit(EXIT_SUCCESS); 
}
