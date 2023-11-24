#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;

void print_tab(int *tab, uint size) {
    printf("[");
    for (uint i = 0; i < size; i++) {
        printf(" %d", tab[i]);
    }
    printf(" ]\n");
}

int nbCapitals(FILE *file) {
    if (!file) {
        fprintf(stderr, "error argument\n");
        return EXIT_FAILURE;
    }
    uint count = 0;
    long starting_pos = ftell(file);
    rewind(file);
    int c = fgetc(file);
    while (c != EOF) {
        if (c >= 'A' && c <= 'Z') {
            count++;
        }
        c = fgetc(file);
    }
    fseek(file, starting_pos, SEEK_SET);
    return count;
}

int addOne(int i) {
    return ++i;
}

int multiplyByTwo(int i) {
    return i*2;
}

void applyOpOnArray(int (*op)(int), int tab[], int size) {
    for (uint i = 0; i < size; i++) {
        tab[i] = (*op)(tab[i]);
    }
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "main needs 2 arguments\n");
        return EXIT_FAILURE;
    }
    if (strcmp("ex1", argv[1]) == 0) {
        FILE *file = fopen("text", "r");
        printf("Capitals count = %d\n",nbCapitals(file));
        fclose(file);
    } else if (strcmp("ex2",argv[1]) == 0) {
        int size = 5;
        int tab[size];
        for (uint i = 0; i < size; i++) tab[i] = i+1;
        print_tab(tab, size);
        applyOpOnArray(&addOne, tab, size);
        applyOpOnArray(&addOne, tab, size);
        applyOpOnArray(&multiplyByTwo, tab, size);
        applyOpOnArray(&addOne, tab, size);
        applyOpOnArray(&multiplyByTwo, tab, size);
        print_tab(tab, size);
    } else if (strcmp("ex3",argv[1]) == 0) {
        // my functions
        char *f1(long l1, long l2);
        char *(*f2(int x))(long, long);
        void f3(char *(*fun)(long, long));
        char *(*(*f4(double *d))(int))(long, long);
        char *(*(*f5(char *(*fun)(long, long)))(int))(long, long);
        // ChatGPT's functions
    } else {
        fprintf(stderr, "incorrect arguments\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}