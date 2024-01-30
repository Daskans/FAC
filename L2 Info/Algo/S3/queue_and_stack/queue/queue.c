#include "queue.h"

#include <assert.h>

struct _queue_t
{
  size_t value;
  struct _queue_t *next;
};

queue_t *
queue_push (queue_t *queue, size_t value)
{
  queue_t *tmp = queue;
  if (!tmp) {
    fprintf(stderr, "not enough memory");
    return EXIT_FAILURE;
  }
  if (queue) {
    while (tmp) {
      tmp = tmp->next;
    }
    tmp->value = value;
    return EXIT_SUCCESS;
  }
  return SIZE_MAX;
}

queue_t *
queue_pop (queue_t *queue)
{
  return NULL;
}

size_t
queue_peek (queue_t *queue)
{
  return 0;
}

bool
queue_is_empty (queue_t *queue)
{
  return true;
}

size_t
queue_print (queue_t *queue, FILE *fd)
{
  return 0;
}

void
queue_delete (queue_t *queue)
{
  return;
}
