#ifndef dna_tH
#define dna_tH
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum nucleo {
    A,
    T,
    G,
    C,
} nucleo;

typedef struct dna {
    nucleo* code;
    size_t size;
} dna_t;

typedef struct tree {
    bool isaleaf;
    // Je ne sais pas faire de champs
} tree_t;

typedef unsigned int uint;


dna_t* createdna(int size);

void freedna(dna_t* d);

tree_t* makeNode(tree_t* t1, tree_t*t2);

tree_t* makeLeaf(dna_t* d);

void freetree(tree_t* t);

int distdna (dna_t* d1, dna_t* d2);

dna_t* readdna (FILE* f);

#endif