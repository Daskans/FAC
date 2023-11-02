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
  if (!list) {
    return NULL;
  }
  return list->next;
}

dlist_t *
dlist_previous (dlist_t *list)
{
  if (!list) {
    return NULL;
  }
  return list->previous;
}

size_t
dlist_get_value (dlist_t *list, size_t index)
{
  if (!list) {
    fprintf(stderr, "list given does not exist\n");
    return NULL;
  }
  dlist_t *temp_list = list;
  for (uint i = 0; i < index; i++) {
    if (!temp_list->next) {
      return NULL;
    }
    temp_list = temp_list->next;
  }
  return temp_list->value;
}

dlist_t *
dlist_set_value (dlist_t *list, size_t index, size_t value)
{
  if (!list && index == 0) {
    dlist_t *list = dlist_append(NULL, value);
    return list;
  } else if ((!list && index != 0)) {
    return NULL;
  }
  dlist_t *temp_list = list;
  for (uint i = 0; i < index; i++) {
    if (!temp_list->next) {
      return NULL;
    }
    temp_list = temp_list->next;
  }
  temp_list->value = value;
  return list;
}

dlist_t *
dlist_get_address (dlist_t *list, size_t index)
{
  if (!list) {
    fprintf(stderr, "list given does not exist\n");
    return NULL;
  }
  for (uint i = 0; i < index; i++) {
    if (!list->next) {
      return NULL;
    }
    list = list->next;
  }
  return list;
}

size_t
dlist_length (dlist_t *list)
{
  size_t length = 0;
  while (list) {
    length++;
    list = list->next;
  }
  return length;
}

size_t
dlist_print (dlist_t *list, FILE *fd)
{
  fprintf(fd, "[");
  size_t char_count = 3;
  if (list) {
    dlist_t *temp_list = list;
    fprintf(fd, " %zu", temp_list->value);
      while (temp_list->next) {
        temp_list = temp_list->next;
        fprintf(fd, ", %zu", temp_list->value);
        char_count += 3;
    }
  }
  fprintf(stdout, " ]\n");
  return char_count;
}

void
dlist_delete (dlist_t *list)
{
  /*while (list) {
    list->value = NULL;
    free(list);
    list = list->next;
  }*/
  return NULL;
}

dlist_t *
dlist_append (dlist_t *list, size_t value)
{
  dlist_t *new_list = malloc(sizeof(dlist_t));
  if (!new_list) {
    fprintf(stderr, "not enough memory\n");
    return NULL;
  }
  new_list->value = value;
  new_list->next = NULL;
  new_list->previous = NULL;
  if (!list) {
    fprintf(stdout, "no list given, new list was created\n");
    return new_list;
  }
  dlist_t *temp_list = list;
  while (temp_list->next) {
    temp_list = temp_list->next;
  }
  temp_list->next = new_list;
  return list;
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
  dlist_t *copy_list = malloc(sizeof(dlist_t));
  if (!list) {
    copy_list = NULL;
  } else {
    copy_list->value = list->value;
    dlist_t *temp_list = list;
    while (temp_list->next) {
      temp_list = temp_list->next;
      dlist_append(copy_list, temp_list->value);
    }
  }
  return copy_list;
}

dlist_t *
dlist_concat (dlist_t *list1, dlist_t *list2)
{
  if (!list1) return list2;
  if (!list2) return list1;
  while (list2) {
    dlist_append(list1, list2->value);
    list2 = list2->next;
  }
  return list1;
}

dlist_t *
dlist_swap (dlist_t *list, size_t index1, size_t index2)
{
  /*if (!list) return NULL;
  dlist_t *temp_list = list;
  for (size_t i = 0; i < index1; i++) {
    if (!temp_list) return NULL;
    temp_list = temp_list->next;
  }
  size_t value1 = temp_list->value;
  for (size_t i = index1; i < index2; i++) {
    if (!temp_list) return NULL;
    temp_list = temp_list->next;
  }
  size_t value2 = temp_list->value;
  temp_list->value = value1;
  for (size_t i = index2; i > index1; i--) {
    if (!temp_list) return NULL;
    temp_list = temp_list->previous;
  }
  temp_list->value = value2;*/
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
  return NULL;
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
