#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <err.h>
#include <string.h>

#include "stack.h"

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

#define STACK_SIZE 10

int
main (void)
{
  /* Check stack_push() */
  printf ("\n"
          "Check stack_push()\n"
          "==================\n");
  stack_t *stack = NULL;
  for (size_t i = 0; i < STACK_SIZE; i++)
    {
      EXPECT (((stack = stack_push (stack, i)) != NULL),
              "stack_push(stack, %zu) != NULL", i);
    }

  /* Check stack_is_empty() */
  printf ("\n"
          "Check stack_is_empty()\n"
          "======================\n");
  EXPECT (stack_is_empty (NULL) == true, "stack_is_empty(NULL) == true");
  EXPECT (stack_is_empty (stack) == false, "stack_is_empty(stack) == false");

  /* Check stack_print() */
  printf ("\n"
          "Check stack_print()\n"
          "===================\n");
  EXPECT_EQ (stack_print (NULL, stdout), 0);
  EXPECT_GT (stack_print (stack, stdout), 0);

  /* Check stack_pop() and stack_peek() */
  printf ("\n"
          "Check stack_pop() and stack_peek()\n"
          "==================================\n");
  EXPECT_EQ (stack_peek (NULL), SIZE_MAX);
  EXPECT_EQ (stack_pop (NULL), NULL);

  size_t value = STACK_SIZE - 1;
  while (!stack_is_empty (stack))
    {
      EXPECT (stack_peek (stack) == value, "stack_peek(stack) == %zu", value);
      stack = stack_pop (stack);
      value--;
    }

  /* Check stack_delete() */
  printf ("\n"
          "Check stack_delete()\n"
          "====================\n");
  stack_delete (NULL);
  EXPECT (true, "stack_delete(NULL)");
  for (size_t i = 0; i < STACK_SIZE; i++)
    {
      stack = stack_push (stack, i);
    }
  stack_delete (stack);
  EXPECT (true, "stack_delete(stack)");

  return EXIT_SUCCESS;
}
