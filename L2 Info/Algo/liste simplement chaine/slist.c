#include "slist.h"

#include <stdint.h>

struct _slist_t
{
	size_t value;
	struct _slist_t *next;
};

slist_t *
slist_append (slist_t *list, size_t value)
{
	slist_t *new_list = malloc(sizeof(slist_t));
	if (new_list == NULL) {
		fprintf(stderr,"Not enough memory");
		return NULL;
	}
	new_list->value = value;
	new_list->next = NULL;
	if (list == NULL) {
		fprintf(stderr,"list given was empty, new list created\n");
		return new_list;
	}
	slist_t *temp_list = list;
	while (temp_list->next) {
		temp_list = temp_list->next;
	}
	temp_list->next = new_list;
	return list;
}

slist_t *
slist_prepend (slist_t *list, size_t value)
{
	slist_t *temp_list = malloc(sizeof(slist_t));
	if (temp_list == NULL) {
		fprintf(stderr,"Not enough memory\n");
		return NULL;
	}
	temp_list->value = value;
	temp_list->next = list;

	return temp_list;
}

void
slist_delete (slist_t *list)
{
	while (list) {
		slist_t *list_next = list->next;
		free(list);
		list = list_next;
	}
}

size_t
slist_length (slist_t *list)
{
	size_t size=0;
	slist_t *temp_list = list;
	while (temp_list) {
		temp_list = temp_list->next;
		size++;
	}
	return size;
}

size_t
slist_get (slist_t *list, size_t index)
{
	if (index > slist_length(list)) {
		fprintf(stderr,"index too big\n");
		return 0;
	}
	slist_t *temp_list = list;
	size_t value = temp_list->value;
	for (uint i = 0; i < index; i++) {
		temp_list = temp_list->next;
		value = temp_list->value;
	}
	return value;
}

size_t
slist_print (slist_t *list, FILE *fd)
{
	size_t size = slist_length(list)-1;
	uint char_numb = 3;
	printf("[ ");
	if (list) {
		fprintf(fd, "%zu", list->value);
		char_numb++;
		slist_t *temp_list = list;
		for (uint i = 0; i < size; i++) {
			temp_list = temp_list->next;
			printf(", %ld", temp_list->value);
			char_numb += 3;
		}
	}
	printf(" ]\n");
	return char_numb;
}

slist_t *
slist_copy (slist_t *list)
{
	slist_t *list_copy = NULL;
	slist_t *temp_list = list;
	while (temp_list) {
		list_copy = slist_append(list_copy, temp_list->value);
		if (!list_copy) {
			return NULL;
		}
		temp_list = temp_list->next;
	}
	return list_copy;
}

slist_t *
slist_concat (slist_t *list1, slist_t *list2)
{
	slist_t *concat_list = slist_copy(list1);
	slist_t *temp_list = concat_list;
	while (temp_list->next) {
		temp_list = temp_list->next;
	}
	slist_t *temp_list2 = list2;
	while (temp_list2) {
		concat_list = slist_append(concat_list, temp_list2->value);
		if (!concat_list) {
			return NULL;
		}
		temp_list2 = temp_list2->next;
	}
  printf("%zu\n", slist_length(concat_list));
	return concat_list;
}

slist_t *
slist_insert_at (slist_t *list, size_t index, size_t value)
{
	if (index == 0) {
		return slist_prepend(list, value);
	}
	if (index > slist_length(list)) {
		fprintf(stderr, "index too big");
		return NULL;
	}
	slist_t *value_insert = malloc(sizeof(slist_t));
	value_insert->value = value;
	slist_t *temp_list = list;
	for (uint i = 0; i < index-1; i++) {
		temp_list = temp_list->next;
	}
	value_insert->next = temp_list->next;
	temp_list->next = value_insert;
	return list;
}

slist_t *
slist_remove (slist_t *list, size_t index)
{
	if (index > slist_length(list)) {
		fprintf(stderr, "index too big");
		return NULL;
	}
	slist_t *temp_list = list;
	for (uint i = 0; i < index-1; i++) {
		temp_list = temp_list->next;
	}
  temp_list->next = temp_list->next->next;
	return list;
}

slist_t *
slist_find (slist_t *list, size_t value)
{
	return NULL;
}

size_t
slist_find_index (slist_t *list, size_t value)
{
	return 0;
}

slist_t *
slist_reverse (slist_t *list)
{
	return NULL;
}

slist_t *
slist_sort (slist_t *list)
{
	return NULL;
}