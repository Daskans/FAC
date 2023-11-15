#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "array.h"


int** createArrayOfArrays(uint size){
    int** array = malloc(size * sizeof(int*));
    if (!array) {
        exit(EXIT_FAILURE);
    }
    uint num = 0;
    for (uint i = 0; i < size; i++) {
        int* subArray = malloc((i+1)*sizeof(int));
        if (!subArray) {
            exit(EXIT_FAILURE);
        }
        for (uint j = 0; j < i+1; j++) {
            num++;
            subArray[j] = num;
        }
        array[i] = subArray;
    }
    return array;
}

void freeArrayOfArrays(int **array, uint size){
    if (size == 0) {
        exit(EXIT_FAILURE);
    }
    if (array) {
        for (uint i = 0; i < size; i++) {
            if (array[i]) {
                free(array[i]);
            }
        }
        free(array);
    }
}

void printArrayOfArrays(int **array, uint size){
    if (!array) {
        exit(EXIT_FAILURE);
    }
    printf("size = %d\n", size);
    for (uint i = 0; i < size; i++) {
        for (uint j = 0; j < i+1; j++) {
            printf(" %d", array[i][j]);
        }
        printf("\n");
    }
}

void writeArrayOfArraysInFile(int **array, uint size, char* fname){
    if (!array || !fname) {
        fprintf(stderr, "invalid argument");
        exit(EXIT_FAILURE);
    }
    FILE* file = fopen(fname, "w");
    if (!file) {
        fprintf(stderr, "file did not compute");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d\n", size);
    for (uint i = 0; i < size; i++) {
        for (uint j = 0; j < i+1; j++) {
            fprintf(file, "%d ", array[i][j]);
        }
        fprintf(file, "\n");
    }
}
// int** readAndCheckArrayOfArraysFromFile(uint* p_size, char*fname){}

/** This main function is given as a sample and can 
 * be changed as needed for for debugging purposes
**/
int main() {
    srand(time(NULL));
    uint n = rand()%20;
    printf("Generating a random array of arrays of size %d\n", n);
    int **arr = createArrayOfArrays(n); // given function
    printArrayOfArrays(arr,n);
    writeArrayOfArraysInFile(arr,n,"foo");
    freeArrayOfArrays(arr,n); 
    /*arr=readAndCheckArrayOfArraysFromFile(&(n),"foo");
    printArrayOfArrays(arr,n);
    freeArrayOfArrays(arr,n);*/
    return EXIT_SUCCESS;
}
