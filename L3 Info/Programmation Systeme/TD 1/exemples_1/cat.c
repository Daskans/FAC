#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

#define BUFSIZE 16

void recopier (void)
{
  // Read characters from STDIN and write to STDOUT
  char buffer[BUFSIZE];
  int r, w;

  do {
    r = read (STDIN_FILENO, buffer, BUFSIZE);
    check_syscall (r, "read");

    w = write (STDOUT_FILENO, buffer, r);
    check_syscall (w, "write");
  } while (r == BUFSIZE);
}

int main (int argc, char *argv[])
{
  recopier ();

  return 0;
}