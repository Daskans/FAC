#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

char *FILENAME = "file.txt";

#define pprintf(format, ...)                                                   \
  printf ("[PID %d] " format, getpid (), ##__VA_ARGS__)

int tube[2];

enum
{
  R,
  W
};

// tr a-z A-Z
void child (void)
{
  close (tube[W]);

  for (;;) {
    char c;
    int n;

    // use to upper (read from pipe, output to STDOUT)
    n = read (tube[R], &c, 1);
    check_syscall (n, "read");

    if (n < 1) {
      break;
    }

    c = toupper (c);
    write (STDOUT_FILENO, &c, 1);
  }
}

// cat -n FILENAME
void father (void)
{
  int newline = 1;
  int line    = 1;
  char str[16];

  close (tube[R]);

  int fd = open (FILENAME, O_RDONLY);
  check_syscall (fd, "Cannot open %s file", FILENAME);

  // cat -n
  for (;;) {
    char c;
    int n = read (fd, &c, 1);
    check_syscall (n, "Cannot read from file %s", FILENAME);

    if (n == 0)
      break;

    if (newline) {
      snprintf (str, 16, "\t%d  ", line);
      write (tube[W], str, strlen (str));
      newline = 0;
    }

    n = write (tube[W], &c, 1);
    check_syscall (n, "Cannot write");

    if (c == '\n') {
      line++;
      newline = 1;
    }
  }
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    FILENAME = argv[1];

  pipe (tube);

  if (fork () != 0)
    father ();
  else
    child ();

  return 0;
}
