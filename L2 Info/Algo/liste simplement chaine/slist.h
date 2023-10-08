#ifndef SLIST_H
#define SLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _slist_t slist_t;

/* Append a new value at the end of the linked-list.
 * Returns the head of the list (unchanged) or NULL on error.
 * Note: append(NULL, value) is used to create a new list. */
slist_t *slist_append (slist_t *list, size_t value);

/* Prepend a new value at the beginning of the linked-list.
 * Returns the new head of the list or NULL on error. */
slist_t *slist_prepend (slist_t *list, size_t value);

/* Delete the whole list and all its elements */
void slist_delete (slist_t *list);

/* Returns the length of the list */
size_t slist_length (slist_t *list);

/* Returns the value stored at position 'index' in the list, 0 if not found. */
size_t slist_get (slist_t *list, size_t index);

/* Print the content of a list and returns the number of printed characters */
size_t slist_print (slist_t *list, FILE *fd);

/* Create a (deep) copy of the list.
 * Returns a pointer to the copy of the list or NULL on error. */
slist_t *slist_copy (slist_t *list);

/* Concatenate two lists in one.
 * Returns the head of the new list or NULL on error. */
slist_t *slist_concat (slist_t *list1, slist_t *list2);

/* Insert the element 'value' at the index 'index'.
 * Returns the new head of the list or NULL on error. */
slist_t *slist_insert_at (slist_t *list, size_t index, size_t value);

/* Remove the element at the index 'index' from the list */
slist_t *slist_remove (slist_t *list, size_t index);

/* Search if the element 'value' is present in the list.
 * Returns a pointer to the first occurrence of it or NULL if not found. */
slist_t *slist_find (slist_t *list, size_t value);

/* Search if the element 'value' is present in the list.
 * Returns its position in the list or SIZE_MAX on error. */
size_t slist_find_index (slist_t *list, size_t value);

/* Reverse the content of the list.
 * Returns the new head of the list or NULL on error. */
slist_t *slist_reverse (slist_t *list);

/* Sort the element of the list in ascending order.
 * Returns the new head of the list or NULL on error. */
slist_t *slist_sort (slist_t *list);

#endif /* SLIST_H */