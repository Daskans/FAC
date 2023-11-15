#ifndef _ARRAY
#define _ARRAY

#include <stdbool.h>

typedef unsigned int uint;

int** createArrayOfArrays(uint size);
void freeArrayOfArrays(int **array, uint size);
void printArrayOfArrays(int **array, uint size);
void writeArrayOfArraysInFile(int **array, uint size, char* fname);
int** readAndCheckArrayOfArraysFromFile(uint* p_size, char*fname);
#endif
