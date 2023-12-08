#include "matrice.h"

struct matrix {
    uint height;
    uint width;
    int **values;
};

void checkMatrix(matrix_t matrix) {
    if (!matrix) {
        fprintf(stderr, "matrix doesn't exist");
        exit(EXIT_FAILURE);
    }
}

void checkCoord(matrix_t matrix, uint i, uint j) {
    checkMatrix(matrix);
    if (i > matrix->height || j > matrix->width) {
        fprintf(stderr, "incorrect coordonates");
        exit(EXIT_FAILURE);
    }
}

matrix_t createMatrix(uint height, uint width) {
    if (height < 1 || width < 1) {
        fprintf(stderr, "incorrect argument");
        exit(EXIT_FAILURE);
    }
    matrix_t matrix = malloc(sizeof(matrix_t));
    checkMatrix(matrix);
    matrix->height = height;
    matrix->width = width;
    matrix->values = malloc(height * sizeof(int*));
    if (!matrix->values) {
        fprintf(stderr, "not enough memory");
        exit(EXIT_FAILURE);
    }
    for (uint i = 0; i < height; i++) {
        matrix->values[i] = calloc(width, sizeof(int));
        if (!matrix->values[i]) {
            fprintf(stderr, "not enough memory");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

void setValue(matrix_t matrix, uint i, uint j, int value) {
    checkMatrix(matrix);
    checkCoord(matrix, i, j);
    matrix->values[i][j] = value;
}

int getValue(matrix_t matrix,  uint i, uint j) {
    checkMatrix(matrix);
    checkCoord(matrix, i, j);
    return matrix->values[i][j];
}

uint getMatrixHeight(matrix_t matrix) {
    checkMatrix(matrix);
    return matrix->height;
}

uint getMatrixWidth(matrix_t matrix) {
    checkMatrix(matrix);
    return matrix->width;
}

void freeMatrix(matrix_t matrix) {
    if (matrix) {
        if (matrix->values) {
            for (uint i = 0; i < matrix->height; i++) {
                if (matrix->values[i]) {
                    free(matrix->values[i]);
                }
            }
            free(matrix->values);
        }
        free(matrix);
    }
}

void printMatrix(matrix_t matrix) {
    checkMatrix(matrix);
    printf("Here's the matrix :\n");
    for (uint i = 0; i < matrix->height; i++) {
        printf("[ ");
        for (uint j = 0; j < matrix->width; j++) {
            printf("%d ", matrix->values[i][j]);
        }
        printf("]\n");
    }
}

