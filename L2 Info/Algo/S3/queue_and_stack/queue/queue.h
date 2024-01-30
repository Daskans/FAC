#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _queue_t queue_t;

/* Push element to the queue.
 * Returns 0 on success or SIZE_MAX otherwise. */
queue_t *queue_push (queue_t *queue, size_t value);

/* Pop an element from the queue.
 * Returns the element on success or SIZE_MAX otherwise. */
queue_t *queue_pop (queue_t *queue);

/* Peek first element of queue.
 * Returns the element on success or SIZE_MAX otherwise. */
size_t queue_peek (queue_t *queue);

/* Check if queue is empty.
 * Returns true if empty, false otherwise. */
bool queue_is_empty (queue_t *queue);

/* Display the queue on file descriptor 'fd'.
 * Returns the number of characters printed. */
size_t queue_print (queue_t *queue, FILE *fd);

/* Delete the queue */
void queue_delete (queue_t *queue);

#endif /* QUEUE_H */
