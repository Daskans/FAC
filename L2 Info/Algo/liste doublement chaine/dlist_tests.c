#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <err.h>
#include <string.h>
#include <time.h>

#include "dlist.h"
#include "sort.h"

/* Colors */
#define GREEN     "\033[32m"        /* Green */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define RED       "\033[31m"        /* Red */
#define BOLDRED   "\033[1m\033[31m" /* Bold Red */
#define RESET     "\033[0m"         /* Reset color */

#define LIST_LENGTH 5

static void
EXPECT (bool test, char *fmt, ...)
{
  fprintf (stdout, "Checking '");

  va_list vargs;
  va_start (vargs, fmt);
  vprintf (fmt, vargs);
  va_end (vargs);

  fprintf (stdout, "': [%s" RESET "]\n",
           (test) ? BOLDGREEN "passed" : BOLDRED "failed");
}

static void
ASSERT (bool test, char *fmt, ...)
{
  fprintf (stdout, "Checking '");

  va_list vargs;
  va_start (vargs, fmt);
  vprintf (fmt, vargs);
  va_end (vargs);

  if (test)
    fprintf (stdout, "': [" BOLDGREEN "passed" RESET "]\n");
  else
    {
      fprintf (stdout, "': (" BOLDRED "critical fail" RESET ") aborting...\n");
      exit (EXIT_FAILURE);
    }
}

int
main (void)
{
  printf ("\nCheck dlist_append()\n"
          "====================\n");
  dlist_t *list = NULL;
  for (size_t i = 0; i < LIST_LENGTH; i++)
    ASSERT (((list = dlist_append (list, i)) != NULL), "dlist_append(%zu)", i);

  printf ("\nCheck dlist_print()\n"
          "===================\n");
  size_t count = dlist_print (NULL, stdout);
  puts ("");
  EXPECT ((count == 3), "dlist_print(NULL, stdout) == \"[ ]\"");
  puts ("");

  count = dlist_print (list, stdout);
  puts ("");
  EXPECT ((count > 0),
          "dlist_print(list, stdout) == \"[ 0, 1, 2, 3, 4 ]\"");

  printf ("\nCheck dlist_get_value()\n"
          "=========================\n");
  EXPECT ((dlist_get_value (NULL, 5) == 0), "(dlist_get_value(NULL, 5) == 0)");
  puts ("");

  for (size_t i = 0; i < LIST_LENGTH; i++)
    EXPECT ((dlist_get_value (list, i) == i), "dlist_get_value(%zu) == %zu", i,
            dlist_get_value (list, i));

  puts ("");
  EXPECT ((dlist_get_value (list, LIST_LENGTH + 1) == 0),
          "(dlist_get_value(list, %zu) == 0)", LIST_LENGTH + 1);

  printf ("\nCheck dlist_set_value()\n"
          "=========================\n");
  EXPECT ((dlist_set_value (NULL, 5, 1) == NULL),
          "(dlist_set_value(NULL, 5, 1) == NULL)");
  puts ("");

  dlist_t *list2;
  EXPECT (((list2 = dlist_set_value (NULL, 0, 1)) != NULL),
          "(dlist_set_value(NULL, 0, 1) != NULL)");
  dlist_delete (list2);
  puts ("");

  for (size_t i = 0; i < LIST_LENGTH; i++)
    EXPECT ((dlist_set_value (list, i, i) == list),
            "dlist_set_value(list, %1$zu, %1$zu) == list", i);

  puts ("");
  EXPECT ((dlist_set_value (list, LIST_LENGTH + 1, 0) == 0),
          "(dlist_set_value(list, %zu, 0) == 0)", LIST_LENGTH + 1);

  printf ("\nCheck dlist_get_address()\n"
          "===========================\n");
  EXPECT ((dlist_get_address (NULL, 5) == NULL),
          "(dlist_get_address(NULL, 5) == NULL)");
  puts ("");

  for (size_t i = 0; i < LIST_LENGTH; i++)
    EXPECT ((dlist_get_address (list, i) != NULL),
            "dlist_get_address(%zu) != %p", i, dlist_get_address (list, i));

  puts ("");
  EXPECT ((dlist_get_address (list, LIST_LENGTH + 1) == NULL),
          "(dlist_get_address(list, %zu) == NULL)", LIST_LENGTH + 1);

  printf ("\nCheck dlist_length()\n"
          "======================\n");
  EXPECT ((dlist_length (NULL) == 0), "dlist_length(NULL) == 0");
  EXPECT ((dlist_length (list) == LIST_LENGTH), "dlist_length(list) == %u",
          LIST_LENGTH);

  printf ("\nCheck dlist_copy()\n"
          "====================\n");
  EXPECT ((dlist_copy (NULL) == NULL), "dlist_copy(NULL) == NULL");
  dlist_t *copy = dlist_copy (list);
  EXPECT ((copy != NULL), "dlist_copy(list) != NULL");
  puts ("");

  /* Check each element */
  for (size_t i = 0; i < LIST_LENGTH; i++)
    EXPECT ((dlist_get_value (list, i) == dlist_get_value (copy, i)),
            "dlist_get_value(list, %1$zu) == dlist_get_value(copy, %1$zu)", i);

  printf ("\nCheck dlist_concat()\n"
          "======================\n");
  EXPECT ((dlist_concat (NULL, NULL) == NULL),
          "dlist_concat (NULL, NULL) == NULL");
  puts ("");

  EXPECT ((dlist_concat (list, NULL) == list),
          "dlist_concat (list, NULL) == list");
  EXPECT ((dlist_length (list) == LIST_LENGTH),
          "dlist_length (list) == LIST_LENGTH");
  puts ("");

  EXPECT ((dlist_concat (NULL, list) == list),
          "dlist_concat (NULL, list) == list");
  EXPECT ((dlist_length (list) == LIST_LENGTH),
          "dlist_length (list) == LIST_LENGTH");
  puts ("");

  EXPECT ((dlist_concat (list, copy) == list),
          "dlist_concat (list, copy) == list");
  EXPECT ((dlist_length (list) == 2 * LIST_LENGTH),
          "dlist_length (list) == %u", 2 * LIST_LENGTH);

  printf ("\nCheck dlist_swap()\n"
          "====================\n");
  EXPECT ((dlist_swap (NULL, 0, 0) == NULL), "dlist_swap(NULL, 0, 0) == NULL");
  EXPECT ((dlist_swap (list, 0, 0) == list), "dlist_swap(list, 0, 0) == list");
  EXPECT ((dlist_swap (list, 0, LIST_LENGTH * 10) == NULL),
          "dlist_swap(list, 0, %zu) == NULL", LIST_LENGTH * 10);
  EXPECT ((dlist_swap (list, LIST_LENGTH * 10, 0) == NULL),
          "dlist_swap(list, %zu, 0) == NULL", LIST_LENGTH * 10);
  puts ("");

  EXPECT ((dlist_swap (list, 0, 1) == list), "dlist_swap(list, 0, 1) == list");
  EXPECT ((dlist_get_value (list, 0) == 1), "dlist_get_value(list, 0) == 1");
  EXPECT ((dlist_get_value (list, 1) == 0), "dlist_get_value(list, 1) == 0");
  puts ("");

  EXPECT ((dlist_swap (list, 1, 0) == list), "dlist_swap(list, 1, 0) == list");
  EXPECT ((dlist_get_value (list, 0) == 0), "dlist_get_value(list, 0) == 0");
  EXPECT ((dlist_get_value (list, 1) == 1), "dlist_get_value(list, 1) == 1");

  printf ("\nCheck dlist_delete()\n"
          "======================\n");
  dlist_delete (list);
  EXPECT ((true), "dlist_delete(list)");

  /* Reinitialize the list with items (again) */
  list = NULL;
  for (size_t i = 0; i < LIST_LENGTH; i++)
    list = dlist_append (list, i);

  printf ("\nCheck dlist_insert_at()\n"
          "=========================\n");
  EXPECT ((dlist_insert_at (NULL, 1, 1) == NULL),
          "dlist_insert_at(NULL, 1, 1) == NULL");

  EXPECT (((list2 = dlist_insert_at (NULL, 0, 1)) != NULL),
          "dlist_insert_at(NULL, 0, 1) != NULL");
  dlist_delete (list2);
  puts ("");

  EXPECT ((dlist_insert_at (list, LIST_LENGTH, 1) == NULL),
          "dlist_insert_at(list, %u, 1) == NULL", LIST_LENGTH);
  EXPECT ((dlist_length (list) == LIST_LENGTH), "dlist_length(list) == %u",
          LIST_LENGTH + 1);

  EXPECT ((dlist_insert_at (list, LIST_LENGTH / 2, 1) == list),
          "dlist_insert_at(list, %u, 1)", LIST_LENGTH / 2);
  EXPECT ((dlist_length (list) == LIST_LENGTH + 1), "dlist_length(list) == %u",
          LIST_LENGTH + 1);

  EXPECT (((list = dlist_insert_at (list, 0, 1)) != NULL),
          "dlist_insert_at(list, 0, 1)");
  EXPECT ((dlist_length (list) == LIST_LENGTH + 2), "dlist_length(list) == %u",
          LIST_LENGTH + 2);

  printf ("\nCheck dlist_remove()\n"
          "======================\n");
  EXPECT ((dlist_remove (NULL, 0) == NULL), "dlist_remove(NULL, 0) == NULL");
  EXPECT ((dlist_remove (NULL, 1) == NULL), "dlist_remove(NULL, 1) == NULL");

  // DEBUG
  printf ("list = ");
  dlist_print (list, stdout);
  puts ("");

  EXPECT (((list = dlist_remove (list, 0)) != NULL),
          "dlist_remove(list, 0) != NULL");
  EXPECT ((dlist_length (list) == LIST_LENGTH + 1), "dlist_length(list) == %u",
          LIST_LENGTH + 1);

  // DEBUG
  printf ("list = ");
  dlist_print (list, stdout);
  puts ("");

  EXPECT ((dlist_remove (list, 1) == list), "dlist_remove(list, 1) == list");
  EXPECT ((dlist_length (list) == LIST_LENGTH), "dlist_length(list) == %u",
          LIST_LENGTH);

  // DEBUG
  printf ("list = ");
  dlist_print (list, stdout);
  puts ("");

  EXPECT ((dlist_remove (list, LIST_LENGTH + 10) == NULL),
          "dlist_remove(list, 1) == NULL");
  EXPECT ((dlist_length (list) == LIST_LENGTH), "dlist_length(list) == %u",
          LIST_LENGTH);

  printf ("\nCheck dlist_find()\n"
          "======================\n");
  EXPECT ((dlist_find (NULL, 0) == NULL), "dlist_find(NULL, 0) == NULL");

  EXPECT ((dlist_find (list, 0) == NULL), "dlist_find(list, 0) == NULL");
  EXPECT ((dlist_find (list, LIST_LENGTH - 1) != NULL),
          "dlist_find(list, %zu) != NULL", LIST_LENGTH - 1);
  EXPECT ((dlist_find (list, LIST_LENGTH / 2) != NULL),
          "dlist_find(list, %zu) != NULL", LIST_LENGTH / 2);

  printf ("\nCheck dlist_find_index()\n"
          "==========================\n");
  EXPECT ((dlist_find_index (NULL, 0) == SIZE_MAX),
          "dlist_find(NULL, 0) == NULL");

  EXPECT ((dlist_find_index (list, 0) == SIZE_MAX),
          "dlist_find(list, 0) == NULL");
  EXPECT ((dlist_find_index (list, LIST_LENGTH - 1) != SIZE_MAX),
          "dlist_find(list, %zu) != NULL", LIST_LENGTH - 1);
  EXPECT ((dlist_find_index (list, LIST_LENGTH / 2) != 0),
          "dlist_find(list, %zu) != NULL", LIST_LENGTH / 2);

  printf ("\nCheck dlist_reverse()\n"
          "=======================\n");
  EXPECT ((dlist_reverse (NULL) == NULL), "dlist_reverse(NULL) == NULL");
  puts ("");

  printf ("list = ");
  dlist_print (list, stdout);
  puts ("");
  EXPECT (((list = dlist_reverse (list)) != NULL),
          "dlist_reverse(list) != NULL");
  printf ("list = ");
  dlist_print (list, stdout);
  puts ("\n");

  list2 = dlist_append (NULL, 1);
  printf ("list2 = ");
  dlist_print (list2, stdout);
  puts ("");
  EXPECT ((dlist_reverse (list2) == list2), "dlist_reverse(list2) == list2");
  printf ("list2 = ");
  dlist_print (list2, stdout);
  puts ("");

  /* Cleaning memory */
  dlist_delete (list);
  dlist_delete (list2);

  printf ("\nCheck dlist_sort()\n"
          "====================\n");
  EXPECT (((sort (NULL)) == NULL), "sort(NULL) == NULL");
  puts ("");

  srandom (time (NULL) * getpid ());
  list = NULL;
  for (size_t i = 0; i < LIST_LENGTH; i++)
    list = dlist_append (list, random () % 100);

  printf ("list = ");
  dlist_print (list, stdout);
  puts ("");

  EXPECT (((list = sort (list)) != NULL), "sort(list) != NULL");

  printf ("list = ");
  dlist_print (list, stdout);
  puts ("\n");

  for (size_t i = 0; i < LIST_LENGTH - 1; i++)
    EXPECT ((dlist_get_value (list, i) <= dlist_get_value (list, i + 1)),
            "dlist_get_value(list, %zu) <= dlist_get_value(list, %zu)", i,
            i + 1);
  puts ("");

  /* Cleaning memory */
  dlist_delete (list);

  return EXIT_SUCCESS;
}
