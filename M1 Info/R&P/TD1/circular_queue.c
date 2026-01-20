#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

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
        new_queue.array[i] = -1;
    }

    return new_queue;
}

bool is_empty(queue_t queue) {
    return queue.count == 0;
}

bool is_full(queue_t queue) {
    return queue.SIZE == queue.count;
}

int push(queue_t *queue, int value) {
    if (is_full(*queue)) {
        fprintf(stderr, "ERROR : queue was full\n");
        exit(EXIT_FAILURE);
    }

    queue->end_i++;
    queue->count++;
    if (queue->end_i == queue->SIZE) {
        queue->end_i = 0;
    }
    queue->array[queue->end_i] = value;

    return EXIT_SUCCESS;
}

int pop(queue_t *queue) {
    if (is_empty(*queue)) {
        fprintf(stderr, "ERROR : queue was empty\n");
        exit(EXIT_FAILURE);
    }

    queue->array[queue->start_i] = -1;
    queue->count--;
    queue->start_i++;
    if (queue->start_i == queue->SIZE) {
        queue->start_i = 0;
    }
    return EXIT_SUCCESS;
}

void clean(queue_t *queue) {
    for (int i = 0; i < queue->SIZE; i++) {
        queue->array[i] = -1;
    }
    free(queue->array);
    queue = NULL;
}

void print(queue_t queue) {
    printf("[ ");
    for (int i = 0; i < queue.SIZE; i++) {
        printf("%d ", queue.array[i]);
    }
    printf("]\n");
    printf("start_i = %d, end_i = %d\n", queue.start_i, queue.end_i);
}

int main(int argc, char* argv[]) {
    queue_t queue = init_queue(10);
    print(queue);

    int num_threads = atoi(argv[1]);
    pthread_t threads[num_threads];


    for (int i = 0; i < num_threads; i++) {
        
    }
    return EXIT_SUCCESS;
}