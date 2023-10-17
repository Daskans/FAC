#ifndef _DYNINTARRAY
#define _DYNINTARRAY

typedef struct{
    int * tab;
    unsigned int capacity;
    unsigned int size;
} dynIntArray;

/* set of provided functions */
dynIntArray* createArray(unsigned int capacity);
void addValueAt(dynIntArray* t, int val, unsigned int ind);
void addValueAsLast(dynIntArray* t, int val);
void printArray(dynIntArray* t);
dynIntArray* copy(dynIntArray* t);
void deleteLastValue(dynIntArray* t);
void deleteValueAt(dynIntArray* t, unsigned int ind);
void deleteAllOccurencesOf(dynIntArray* t, int val);
unsigned int size(dynIntArray* t);
void freeArray(dynIntArray* t);
/* end of set of provided functions */

#endif