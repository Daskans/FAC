#include <stdlib.h>
#include <stdio.h>
#include "dynIntArray.h"

typedef unsigned int uint;

dynIntArray* createArray(unsigned int capacity){
    dynIntArray *array = malloc(sizeof(dynIntArray));
    int *new_tab = malloc(capacity * sizeof(int));
    if (new_tab == NULL) {
        fprintf(stderr, "Not enough memory");   
        exit(EXIT_FAILURE);
    }
    array->tab = new_tab;
    array->capacity = capacity;
    array->size = 0;
    return array;
}

void addValueAt(dynIntArray* t, int val, unsigned int ind){
    if (t == NULL || t->tab == NULL || ind > t->size) {
        fprintf(stderr, "Incorrect argument at addValueAt\n");
        exit(EXIT_FAILURE);
    }
    if (t->size >= t->capacity) {
        int *temp_list = realloc(t->tab, 2 * t->capacity * sizeof(int));
        if (temp_list == NULL) {
            fprintf(stderr, "Not enough memory");
            exit(EXIT_FAILURE);
        }
        t->tab = temp_list;
        t->capacity = 2*t->capacity;
    }
    for (uint i = t->size; i > ind; i--) {
        t->tab[i] = t->tab[i-1];
    }
    t->tab[ind] = val;
    t->size++;
}

void addValueAsLast(dynIntArray* t, int val){
    if (t == NULL || t->tab == NULL) {
        fprintf(stderr, "Incorrect argument at addValueAsLast\n");
        exit(EXIT_FAILURE);
    }
    if (t->size >= t->capacity) {
        int *temp_list = realloc(t->tab, 2 * t->capacity * sizeof(int));
        if (temp_list == NULL) {
            fprintf(stderr, "Not enough memory");   
            exit(EXIT_FAILURE);
        }
        t->tab = temp_list;
        t->capacity = 2*t->capacity;
    }
    t->tab[t->size] = val;
    t->size++;
}

void printArray(dynIntArray* t){
    if (t == NULL || t->tab == NULL) {
        fprintf(stderr, "Incorrect argument at printArray\n");
        exit(EXIT_FAILURE);
    }
    for (uint i = 0; i < t->size; i++) {
        printf(" %d", t->tab[i]);
    }
    printf("\n");
}

// dynIntArray* copy(dynIntArray* t){}

void deleteLastValue(dynIntArray* t){
    if (t == NULL || t->tab == NULL || t->size == 0) {
        fprintf(stderr, "Incorrect argument at printArray\n");
        exit(EXIT_FAILURE);
    }
    t->size--;
}

// void deleteValueAt(dynIntArray* t, unsigned int ind){}
// void deleteAllOccurencesOf(dynIntArray* t, int val){}

unsigned int size(dynIntArray* t){
    if (t == NULL || t->tab == NULL) {
        fprintf(stderr, "Incorrect argument at printArray\n");
        exit(EXIT_FAILURE);
    }
    return t->size;
}

void freeArray(dynIntArray* t){
    if (t == NULL) {
        fprintf(stderr,"Incorrect argument at freeArray\n");
    }
    free(t->tab);
    free(t);
}

/** This main function is given as a sample and can 
 * be changed as needed for debugging purpose
 **/
int main(void){
    dynIntArray * p = createArray(5);
    printf("(main 1)\n size : %d\n capacity : %d\n", p->size, p->capacity);
    if (p==NULL){
        fprintf(stderr,"Not enough memory!\n");
        return EXIT_FAILURE;
    }
    unsigned int i;
    addValueAsLast(p, 2);
    printf("(main 2)\nsize : %d\n capacity : %d\n", p->size, p->capacity);
    printArray(p);
    printf("addValueAt x10:\n");
    for (i=0 ; i<10 ; i++){
        addValueAt(p,20-i,i);
    }
    printArray(p);
    /*printf("addValueAsLast x10:\n");
    for (i = 10 ; i > 0 ; i--){
        addValueAsLast(p,20-i+1);
    }
    printArray(p);

    printf("deleteLastValue x5:\n");
    dynIntArray * p2 = copy(p);
    for (i = 5 ; i > 0 ; i--){
        deleteLastValue(p);
    }
    printArray(p);
    printf("deleteValueAt x5:\n");
    for (i = 5 ; i > 0 ; i--){
        deleteValueAt(p2,i);
    }
    printArray(p2);
    deleteAllOccurencesOf(p,12);
    printArray(p);*/
    freeArray(p);
    //freeArray(p2);
    return EXIT_SUCCESS;
}