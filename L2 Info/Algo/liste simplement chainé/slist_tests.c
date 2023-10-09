#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <err.h>
#include <string.h>

#include "slist.h"

/* Colors */
#define GREEN     "\033[32m"        /* Green */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define RED       "\033[31m"        /* Red */
#define BOLDRED   "\033[1m\033[31m" /* Bold Red */
#define RESET     "\033[0m"         /* Reset color */

#define LIST_LENGTH 10

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
    fprintf (stdout, "': (passed)\n");
  else
    {
      fprintf (stdout, "': (" BOLDRED "critical fail" RESET ") aborting...\n");
      exit (EXIT_FAILURE);
    }
}

int
main (void)
{
  slist_t *list = NULL;

  printf ("\nCheck slist_append()\n"
          "====================\n");
  for (size_t i = 1; i < LIST_LENGTH; i++)
    EXPECT (((list = slist_append (list, i)) != NULL), "slist_append(%zu)", i);

  printf ("\nCheck slist_prepend()\n"
          "====================\n");
  EXPECT (((list = slist_prepend (list, 0)) != NULL), "slist_prepend(0)");

  printf ("\nCheck slist_print()\n"
          "===================\n");
  EXPECT ((slist_print (list, stdout) > 0),
          "slist_print(list, stdout) == \"[ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]\"");
  EXPECT ((slist_print (NULL, stdout) == 3),
          "slist_print(NULL, stdout) == \"[ ]\"");

  printf ("\nCheck slist_get()\n"
          "=================\n");
  for (size_t i = 0; i < LIST_LENGTH; i++)
    EXPECT ((slist_get (list, i) == i), "slist_get(%1$zu) == %1$zu", i);

  printf ("\nCheck slist_length()\n"
          "======================\n");
  EXPECT ((slist_length (list) == LIST_LENGTH), "slist_length(list) == %u",
          LIST_LENGTH);

  printf ("\nCheck slist_copy()\n"
          "====================\n");
  slist_t *copy = slist_copy (list);
  EXPECT ((copy != NULL), "slist_copy(list) != NULL");
  EXPECT ((slist_copy (NULL) == NULL), "slist_copy(NULL) == NULL");

  /* Check each element */
  for (size_t i = 0; i < LIST_LENGTH; i++)
    EXPECT ((slist_get (list, i) == slist_get (copy, i)),
            "slist_get(list, %1$zu) == slist_get(copy, %1$zu)", i);

  printf ("\nCheck slist_concat()\n"
          "======================\n");
  slist_t *concat = slist_concat(list, copy);
  EXPECT ((concat == concat),
          "slist_concat (list, copy) == concat");
  EXPECT ((slist_length (concat) == 2 * LIST_LENGTH),
          "slist_length (concat) == %u", 2 * LIST_LENGTH);

  printf ("\nCheck slist_insert_at()\n"
          "======================\n");
  EXPECT ((slist_insert_at (list, 5, 88) == list),
          "slist_insert_at (list, 5, 88) == list");
  EXPECT ((slist_length (list) == LIST_LENGTH + 1),
          "slist_length (list) == %u", LIST_LENGTH + 1);

  printf ("\nCheck slist_remove()\n"
          "======================\n");
  EXPECT ((slist_remove (list, 5) == list),
          "slist_remove (list, 5) == list");
  EXPECT ((slist_length (list) == LIST_LENGTH ),
          "slist_length (list) == %u", LIST_LENGTH );

  printf ("\nCheck slist_delete()\n"
          "======================\n");
  slist_delete (list);
  EXPECT ((true), "slist_delete(list)");

  return EXIT_SUCCESS;
}