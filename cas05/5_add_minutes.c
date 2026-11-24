/* Ispisati datum i vreme koji se dobijaju kada na trenutno vreme dodamo m minuta.
 * Program kao argument komandne linije dobija broj m i ispisuje na standardni izlaz
 * datum i vreme.
 *
 * NAPOMENA: isprobati sa primerima gde je m>=60.
 *
 * Poziv programa:
 * ./a.out m
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <time.h>

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

    const time_t now = time(NULL);
    struct tm *brokenTime = localtime(&now);
    brokenTime->tm_min += atoi(argv[1]);

    time_t new = mktime(brokenTime);

    printf("%s\n", ctime(&new));

    exit(EXIT_SUCCESS);
}