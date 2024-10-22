#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

char *message = "Ceci est un message qui ne paie pas de mine, mais qui se "
                "révèle redoutablement long en pratique, sans toutefois "
                "atteindre non plus des proportions gigantesques...\n";

enum { R, W };

int main (int argc, char *argv[])
{
  int tube [2] = { -1, -1 };

  pipe (tube);

  printf ("pipe -> %d %d \n", tube[0], tube[1]);

  // TODO: write something into the pipe
  write (tube[1], message, strlen(message));
  close (tube[1]);

  for(;;) {
    char buffer;
    int n;

    // TODO: read from pipe
    n = read (tube[0], &buffer, 1);
    check_syscall (n, "read");

    if (n < 1)
      break;

    write (STDOUT_FILENO, &buffer, 1);
  }

  close (tube[0]);
  
  return 0;
}
