#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue {
    int* array;
    const int SIZE;
    int count;
    int start_i;
    int end_i;
} queue_t;

queue_t init_queue(int size) {
    queue_t new_queue = 
    {
        malloc(size * sizeof(int)),
        size,
        0,
        0,
        -1
    };

    for (int i = 0; i < size; i++) {
        new_queue.array[i] = NULL;
    }

    return new_queue;
}

bool is_empty(queue_t queue) {
    for (int i = 0; i < queue.SIZE; i++) {
        if (queue.array[i] == -1) {
            return false;
        }
    }
    return true;
}

bool is_full(queue_t queue) {
    return queue.SIZE - queue.count == 0;
}

int push(queue_t *queue, int value) {
    if (is_full(*queue)) {
        fprintf(stderr, "ERROR : queue was full\n");
        exit(EXIT_FAILURE);
    }

    queue->end_i++;
    queue->count++;
    queue->array[queue->end_i] = value;

    return EXIT_SUCCESS;
}

int pop(queue_t *queue) {
    if (is_empty(*queue)) {
        fprintf(stderr, "ERROR : queue was empty\n");
        exit(EXIT_FAILURE);
    }

    return queue->start_i++;
}

void clean(queue_t *queue) {
    for (int i = 0; i < queue->SIZE; i++) {
        queue->array[i] = -1;
    }
    free(queue->array);
    queue = NULL;
}

int main() {
    queue_t queue = init_queue(10);
    return EXIT_SUCCESS;
}