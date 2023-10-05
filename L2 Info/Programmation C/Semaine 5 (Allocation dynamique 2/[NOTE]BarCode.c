#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "barcode.h"

typedef unsigned int uint;

typedef struct barCode barCode_t;

barCode_t generateBarCode(uint s) {
    if (s<3) {
        fprintf(stderr, "size is too small\n");
        exit(EXIT_FAILURE);
    }
    uint *tab = malloc(s*sizeof(uint));
    if (tab==NULL) {
        fprintf(stderr, "Not enough memory\n");
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

void printBarCode(barCode_t codebar, uint height) {
    if (height==0) exit(EXIT_FAILURE);
    for (uint i=0; i<height; i++) printLine(codebar);
}

int main(int argc, char*argv[]) {
    int seed = time(NULL);
    srand(seed);
    uint randSize = (rand()%10)+1;
    printf("Generating a bar code of size %u\n",randSize);
    barCode_t codebar = generateBarCode(randSize);
    printBarCode(codebar, 5);
    freeBarCode(codebar);
    return EXIT_SUCCESS;
}