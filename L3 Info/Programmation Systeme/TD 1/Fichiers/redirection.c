#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>

#include "error.h"

void quelques_prints (void)
{
  printf ("Juste");
  printf (" histoire");
  printf (" de tester...\n");
  printf ("...que la redirection");
  printf (" marche !\n");
}

void rediriger_vers (void (*f)(void), char *file)
{

  int log =  open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
  check_syscall (log, "Cannot open file %s", file);
  int backup = dup(STDOUT_FILENO);
  dup2(log, STDOUT_FILENO);
  close(log);

  f();
  
  dup2(backup, STDOUT_FILENO);
  close(backup);
}

int main(int argc, char *argv[])
{
  printf ("*** DEBUT ***\n");

  rediriger_vers (quelques_prints, "sortie.txt");

  printf ("*** FIN ***\n");

  return EXIT_SUCCESS;
}
  
