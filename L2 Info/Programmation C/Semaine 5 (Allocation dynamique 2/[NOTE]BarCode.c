#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "barcode.h"

typedef unsigned int uint;

typedef struct barCode barCode_t;

barCode_t generateBarCode(uint s) {
    if (s<3) {
        fprintf(stderr, "size is too small");
        exit(EXIT_FAILURE);
    }
    uint *tab = malloc(s*sizeof(uint));
    if (tab==NULL) {
        fprintf(stderr, "Not enough memory");
        exit(EXIT_FAILURE);
    }
    barCode_t codebar;
    codebar.size = s;
    for (uint i=0; i<s; i++) tab[i]=(rand()%5)+1;
    codebar.code = tab;
    return codebar;
}

void freeBarCode(barCode_t codebar) {
    free(codebar.code);
}

void printLine(barCode_t codebar) {
    if (codebar.size>=3 && codebar.code!=NULL) {
        for (uint i=0; i<codebar.size; i++) {
            if (i%2==0) for (uint j=0; j<codebar.code[i]; j++) printf("*");
            else for (uint j=0; j<codebar.code[i]; j++) printf(" ");
        } printf("\n");
    } else exit(EXIT_FAILURE);
}

int main(int argc, char*argv[]) {
    struct barCode b;
    int seed = time(NULL);
    srand(seed); //initialize the pseudo random generator seed
    unsigned int randSize= rand()%10; // generate a random number between 0 and 9;
    printf("Generating a bar code of size %u\n",randSize+1);
    b=generateBarCode(randSize+1); // function to be defined
    printBarCode(b,10); // given function
    freeBarCode(b); // given function
    return EXIT_SUCCESS;
}