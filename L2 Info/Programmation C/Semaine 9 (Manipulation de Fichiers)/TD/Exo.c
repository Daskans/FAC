#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[SIZE];
    unsigned int number;
    int* values;
} sequence_t;

void printSequence (sequence* seq) {
    writeSequence(stdout, seq);
}

void writeSequence (FILe *file, sequence* seq) {
    if (!seq || !file) {
        fprintf(stderr, "invalid argument");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d first number of the %s sequence:\n", seq->number, seq->name);
    fprintf(file, "%d", values[0])
    for (int i = 1; i < seq->number; i++) {
        fprintf(file, "%d", values[i]);
    }
    fprintf(file, "\n");
}

void readSequence(File *file, sequence* seq) {
    if (!seq || !file) {
        fprintf(stderr, "invalid argument");
        exit(EXIT_FAILURE);
    }
    int *seq->values = malloc(sizeof(int))
    fscanf(file, "%d first number of the %s sequence:\n", &(seq->number), seq->name);
    fscanf(file, "%d", values[0])
    for (int i = 1; i < seq->number; i++) {
        fscanf(file, "%d", &(seq->values[i]));
    }
    fscanf(file, "\n");
}

int main(void) {
    sequence *seq = malloc(sizeof(sequence));
    seq->number = 5;
    for (int i = 0; i < seq->number)
}