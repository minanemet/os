#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {

    int korisnik = 2;

    if((korisnik = 4) == 3) {
        printf("Korisnik je: %d\n", korisnik);
    } else {
        printf("Korisnik nije 3!\n");
    }

    return 0;
}