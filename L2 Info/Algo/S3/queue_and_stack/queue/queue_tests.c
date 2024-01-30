#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <err.h>
#include <string.h>

#include "queue.h"

/* Colors */
#define GREEN "\033[32m"            /* Green */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define RED "\033[31m"              /* Red */
#define BOLDRED "\033[1m\033[31m"   /* Bold Red */
#define RESET "\033[0m"             /* Reset color */

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

#define EXPECT_EQ(a, b) EXPECT ((a) == (b), #a " == " #b)
#define EXPECT_NE(a, b) EXPECT ((a) != (b), #a " != " #b)
#define EXPECT_LT(a, b) EXPECT ((a) < (b), #a " < " #b)
#define EXPECT_LE(a, b) EXPECT ((a) <= (b), #a " <= " #b)
#define EXPECT_GT(a, b) EXPECT ((a) > (b), #a " > " #b)
#define EXPECT_GE(a, b) EXPECT ((a) >= (b), #a " >= " #b)

#define EXPECT_STREQ(a, b) EXPECT (strcmp (a, b) == 0, #a " == " #b)
#define EXPECT_STRNE(a, b) EXPECT (strcmp (a, b) != 0, #a " != " #b)

#define ASSERT_EQ(a, b) ASSERT ((a) == (b), #a " == " #b)
#define ASSERT_NE(a, b) ASSERT ((a) != (b), #a " != " #b)
#define ASSERT_LT(a, b) ASSERT ((a) < (b), #a " < " #b)
#define ASSERT_LE(a, b) ASSERT ((a) <= (b), #a " <= " #b)
#define ASSERT_GT(a, b) ASSERT ((a) > (b), #a " > " #b)
#define ASSERT_GE(a, b) ASSERT ((a) >= (b), #a " >= " #b)

#define ASSERT_STREQ(a, b) ASSERT (strcmp (a, b) == 0, #a " == " #b)
#define ASSERT_STRNE(a, b) ASSERT (strcmp (a, b) != 0, #a " != " #b)

#define QUEUE_SIZE 10

int
main (void)
{
  /* Check queue_push() */
  printf ("\n"
          "Check queue_push()\n"
          "==================\n");
  queue_t *queue = NULL;
  for (size_t i = 0; i < QUEUE_SIZE; i++)
    {
      EXPECT (((queue = queue_push (queue, i)) != NULL),
              "queue_push(queue, %zu) != NULL", i);
    }

  /* Check queue_is_empty() */
  printf ("\n"
          "Check queue_is_empty()\n"
          "======================\n");
  EXPECT (queue_is_empty (NULL) == true, "queue_is_empty(NULL) == true");
  EXPECT (queue_is_empty (queue) == false, "queue_is_empty(queue) == false");

  /* Check queue_print() */
  printf ("\n"
          "Check queue_print()\n"
          "===================\n");
  EXPECT_EQ (queue_print (NULL, stdout), 0);
  EXPECT_GT (queue_print (queue, stdout), 0);

  /* Check queue_pop() and queue_peek() */
  printf ("\n"
          "Check queue_pop() and queue_peek()\n"
          "==================================\n");
  EXPECT_EQ (queue_peek (NULL), SIZE_MAX);
  EXPECT_EQ (queue_pop (NULL), NULL);

  size_t value = 0;
  while (!queue_is_empty (queue))
    {
      EXPECT (queue_peek (queue) == value, "queue_peek (queue) == %zu", value);
      queue = queue_pop (queue);
      value++;
    }

  /* Check queue_delete() */
  printf ("\n"
          "Check queue_delete()\n"
          "====================\n");
  queue_delete (NULL);
  EXPECT (true, "queue_delete(NULL)");
  for (size_t i = 0; i < QUEUE_SIZE; i++)
    {
      queue = queue_push (queue, i);
    }
  queue_delete (queue);
  EXPECT (true, "queue_delete(queue)");

  return EXIT_SUCCESS;
}
