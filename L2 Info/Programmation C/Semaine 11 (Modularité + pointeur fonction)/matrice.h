#ifndef MATRICE_H
#define MATRICE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct matrix* matrix_t;
typedef unsigned int uint;

matrix_t createMatrix(uint height, uint width);
void setValue(matrix_t matrix, uint i, uint j, int value);
int getValue(matrix_t matrix,  uint i, uint j);
uint getMatrixHeight(matrix_t matrix);
uint getMatrixWidth(matrix_t matrix);
void freeMatrix(matrix_t matrix);
void printMatrix(matrix_t matrix);

#endif /*MATRICE_H*/