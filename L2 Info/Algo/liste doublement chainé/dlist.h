#ifndef DLIST_H
#define DLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _dlist_t dlist_t;
/*
struct _dlist_t
{
  size_t value;
  struct _dlist_t *next;
  struct _dlist_t *previous;
};*/

/* Returns the next element of the list, NULL on empty list */
dlist_t *dlist_next (dlist_t *list);

/* Returns the previous element of the list, NULL on empty list */
dlist_t *dlist_previous (dlist_t *list);

/* Returns the value of the element stored at position 'index' in 'list',
 * 0 if not found. */
size_t dlist_get_value (dlist_t *list, size_t index);

/* Set the value of the element stored at position 'index' in 'list'.
 * Returns the head of the list or NULL on error. */
dlist_t *dlist_set_value (dlist_t *list, size_t index, size_t value);

/* Returns the address of the element at position 'index' in 'list',
 * NULL if not found. */
dlist_t *dlist_get_address (dlist_t *list, size_t index);

/* Returns the length of the list */
size_t dlist_length (dlist_t *list);

/* Print the content of a list and returns the number of printed characters */
size_t dlist_print (dlist_t *list, FILE *fd);

/* Delete the whole list and all its elements */
void dlist_delete (dlist_t *list);

/* Append a new value at the end of the linked-list.
 * Returns the head of the list (unchanged) or NULL on error.
 * Note: append(NULL, value) is used to create a new list. */
dlist_t *dlist_append (dlist_t *list, size_t value);

/* Prepend a new value at the beginning of the linked-list.
 * Returns the new head of the list or NULL on error. */
dlist_t *dlist_prepend (dlist_t *list, size_t value);

/* Create a (deep) copy of the list.
 * Returns a pointer to the copy of the list or NULL on error. */
dlist_t *dlist_copy (dlist_t *list);

/* Concatenate two lists in one.
 * Returns the head of the new list or NULL on error. */
dlist_t *dlist_concat (dlist_t *list1, dlist_t *list2);

/* Swap two elements given by index in a list.
 * Returns the head of the new list or NULL on error. */
dlist_t *dlist_swap (dlist_t *list, size_t index1, size_t index2);

/* Insert the element 'value' at the index 'index'.
 * Returns the new head of the list or NULL on error. */
dlist_t *dlist_insert_at (dlist_t *list, size_t index, size_t value);

/* Remove the element at the index 'index' from the list */
dlist_t *dlist_remove (dlist_t *list, size_t index);

/* Search if the element 'value' is present in the list.
 * Returns a pointer to the first occurrence of it or NULL if not found. */
dlist_t *dlist_find (dlist_t *list, size_t value);

/* Search if the element 'value' is present in the list.
 * Returns its position in the list or SIZE_MAX on error. */
size_t dlist_find_index (dlist_t *list, size_t value);

/* Reverse the content of the list.
 * Returns the new head of the list or NULL on error. */
dlist_t *dlist_reverse (dlist_t *list);

#endif /* DLIST_H */