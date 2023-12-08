#include "matrice.h"

int main(int argc, char* argv[]) {
    uint height = 10;
    uint width = 10;
    if (argc == 3) {
        height = atoi(argv[1]);
        width = atoi(argv[2]);
    } else {
        printf("no sizes were given so it was created with a size of (10,10)");
    }
    srand(time(NULL));
    matrix_t matrix = createMatrix(height, width);
    for (uint k = 0; k < rand()%(height*width); k++) {
        setValue(matrix, rand()%height, rand()%width, 1+rand()%9);
    }
    printMatrix(matrix);
    freeMatrix(matrix);
    return EXIT_SUCCESS;
}