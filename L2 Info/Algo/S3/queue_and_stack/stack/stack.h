#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _stack_t stack_t;

/* Push element to the stack.
 * Returns 0 on success or SIZE_MAX otherwise. */
stack_t *stack_push (stack_t *stack, size_t value);

/* Pop an element from the stack.
 * Returns the element on success or SIZE_MAX otherwise. */
stack_t *stack_pop (stack_t *stack);

/* Peek first element of stack.
 * Returns the element on success or SIZE_MAX otherwise. */
size_t stack_peek (stack_t *stack);

/* Check if stack is empty.
 * Returns true if empty, false otherwise. */
bool stack_is_empty (stack_t *stack);

/* Display the stack on file descriptor 'fd'.
 * Returns the number of characters printed. */
size_t stack_print (stack_t *stack, FILE *fd);

/* Delete the stack */
void stack_delete (stack_t *stack);

#endif /* STACK_H */
