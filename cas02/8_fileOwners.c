#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

/*
Napisati:
a) Funckiju koja na osnovu user ID-a vraca njegovo ime.

b) Funkciju koja na osnovu group ID-a vraca njeno ime.

c) Program koji koriscenjem prethodne dve funckije
ispisuje naziv vlasnika i grupe vlasnika za fajl cija se
putanja dobija kao argument komandne linije.

Poziv programa:
./fileinfo filePath
*/

#define check_error(cond, msg)\
 do {\
    if(!(cond)){\
        perror(msg);\
        fprintf(stderr, "File: %s, Function: %s, Line: %d\n", __FILE__, __func__, __LINE__);\
        exit(EXIT_FAILURE);\
    }\
} while (0)

char *get_user_name_by_id(const uid_t uid) {
    struct passwd *korisnik = getpwuid(uid);
    check_error(korisnik != NULL, "getpwuid");

    return korisnik->pw_name;
}

char *get_group_name_by_id(const uid_t gid) {
    struct group *grupa = getgrgid(gid);
    check_error(grupa != NULL, "getgrgid");

    return grupa->gr_name;
}

char *trim_filepath(char *filepath) {
    char *last_slash = strrchr(filepath, '/');
    return last_slash + 1;
}


int main(int argc, char **argv) {
    check_error(argc == 2, "./a.out uid");

    //uid_t id = atoi(argv[1]);

    //char *uname =  get_user_name_by_id(id);
    //printf("id = %s, korisnicko ime = %s\n", argv[1], uname);

    // char *gname = get_group_name_by_id(id);
    // printf("id = %s, ime grupe = %s\n", argv[1], gname);

    struct stat fajl;
    stat(argv[1], &fajl);

    char *filepath = trim_filepath(argv[1]);

    printf("Korisnik za fajl %s: %s, grupa: %s\n", 
        filepath, 
        get_user_name_by_id(fajl.st_uid), 
        get_group_name_by_id(fajl.st_gid)
    );

    exit(EXIT_SUCCESS);
}