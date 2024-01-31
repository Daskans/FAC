#include "dlist.h"

#include <stdint.h>

struct _dlist_t
{
  size_t value;
  struct _dlist_t *next;
  struct _dlist_t *previous;
};

dlist_t *
dlist_next (dlist_t *list)
{
  return NULL;
}

dlist_t *
dlist_previous (dlist_t *list)
{
  return NULL;
}

size_t
dlist_get_value (dlist_t *list, size_t index)
{
  return 0;
}

dlist_t *
dlist_set_value (dlist_t *list, size_t index, size_t value)
{
  return NULL;
}

dlist_t *
dlist_get_address (dlist_t *list, size_t index)
{
  return NULL;
}

size_t
dlist_length (dlist_t *list)
{
  return 0;
}

size_t
dlist_print (dlist_t *list, FILE *fd)
{
  return 0;
}

void
dlist_delete (dlist_t *list)
{
  return;
}

dlist_t *
dlist_append (dlist_t *list, size_t value)
{
  return NULL;
}

dlist_t *
dlist_prepend (dlist_t *list, size_t value)
{
  return NULL;
}

/* This signature makes indistinguishable the copy of an empty list (NULL)
 * and an "out-of-memory" error. What can we do here? */
dlist_t *
dlist_copy (dlist_t *list)
{
  return NULL;
}

dlist_t *
dlist_concat (dlist_t *list1, dlist_t *list2)
{
  return NULL;
}

dlist_t *
dlist_swap (dlist_t *list, size_t index1, size_t index2)
{
  return NULL;
}

dlist_t *
dlist_insert_at (dlist_t *list, size_t index, size_t value)
{
  return NULL;
}

dlist_t *
dlist_remove (dlist_t *list, size_t index)
{
  if (list == NULL)
    return NULL;

  /* Special case: removing first element */
  if (index == 0)
    {
      dlist_t *next = list->next;
      free (list);
      return next;
    }

  /* Find the index-th element */
  size_t count = 0;
  dlist_t *current = list;
  while (count++ < index && current != NULL)
    current = current->next;

  /* If the list is shortest than the index, returns NULL */
  if (count < index)
    return NULL;

  /* Re-link the chain */
  dlist_t *next = current->next, *previous = current->previous;
  if (previous != NULL)
    previous->next = next;
  if (next != NULL)
    next->previous = previous;
  free (current);

  return list;
}

dlist_t *
dlist_find (dlist_t *list, size_t value)
{
  return NULL;
}

size_t
dlist_find_index (dlist_t *list, size_t value)
{
  return SIZE_MAX;
}

dlist_t *
dlist_reverse (dlist_t *list)
{
  return NULL;
}
