/*
Poziv programa:
./a.out pathToFile

Program treba da zameni prava pristupa koje ima grupa
sa pravima pristupa koje imaju ostali.
('man 2 stat' i 'man 7 inode' sadrze sve sto je potrebno)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>

#define check_error(cond, msg)\
    do {\
        if(!(cond)) {\
            perror(msg);\
            fprintf(stderr, "File: %s, line: %d, func: %s\n", __FILE__, __LINE__, __func__);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

int main(int argc, char** argv) {
    check_error(argc == 2, "./a.out pathToFile");

    struct stat fileInfo;
    stat(argv[1], &fileInfo);

    mode_t fileMods = fileInfo.st_mode;
    mode_t pravaPristupa = 0;

    if(fileMods & S_IRUSR) {
        pravaPristupa |= S_IRUSR;
    }
    if(fileMods & S_IWUSR) {
        pravaPristupa |= S_IWUSR;
    }
    if(fileMods & S_IXUSR) {
        pravaPristupa |= S_IXUSR;
    }

    if(fileMods & S_IRGRP) {
        pravaPristupa |= S_IROTH;
    }
    if(fileMods & S_IWGRP) {
        pravaPristupa |= S_IWOTH;
    }
    if(fileMods & S_IXGRP) {
        pravaPristupa |= S_IXOTH;
    }

    if(fileMods & S_IROTH) {
        pravaPristupa |= S_IRGRP;
    }
    if(fileMods & S_IWOTH) {
        pravaPristupa |= S_IWGRP;
    }
    if(fileMods & S_IXOTH) {
        pravaPristupa |= S_IXGRP;
    }

    check_error(chmod(argv[1], pravaPristupa) != -1, "chmod");

    exit(EXIT_SUCCESS);
}