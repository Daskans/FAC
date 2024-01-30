#include "stack.h"

#include <assert.h>

struct _stack_t
{
  size_t value;
  struct _stack_t *next;
};

stack_t *
stack_push (stack_t *stack, size_t value)
{
  return NULL;
}

stack_t *
stack_pop (stack_t *stack)
{
  return NULL;
}

size_t
stack_peek (stack_t *stack)
{
  return 0;
}

bool
stack_is_empty (stack_t *stack)
{
  return true;
}

size_t
stack_print (stack_t *stack, FILE *fd)
{
  return 0;
}

void
stack_delete (stack_t *stack)
{
  return;
}
