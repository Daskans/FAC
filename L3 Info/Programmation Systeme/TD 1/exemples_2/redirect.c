#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

char *filename = "log.txt";

void afficher (char *msg)
{
  printf ("Hello World! (%s)\n", msg);
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    filename = argv[1];

  afficher ("Avant");
  
  int fd = open (filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  check_syscall (fd, "Cannot open file %s", filename);

  // TODO Redirect STDOUT to file
  int backup = dup (STDOUT_FILENO);

  dup2 (fd, STDOUT_FILENO);
  close (fd);

  afficher ("Après");

  // TODO: try to restore "default STDOUT"
  dup2 (backup, STDOUT_FILENO);
  close (backup);

  afficher ("Enfin");

  return 0;
}
