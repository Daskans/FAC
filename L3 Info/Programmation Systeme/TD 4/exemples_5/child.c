#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

pid_t pid = 12;

void my_sig_handler (int sig)
{
  pprintf ("I received signal \"%s\"\n", strsignal (sig));

  // TODO: waitpid
  //int r = waitpid (-1, NULL, WNOHANG);
  int r = waitpid (pid, NULL, 0);
  pprintf ("Wait returned %d\n", r);
}

int main (int argc, char *argv[])
{
  struct sigaction sa;

  sa.sa_flags = 0;
  sigemptyset (&sa.sa_mask);
  sa.sa_handler = my_sig_handler;
  sigaction (SIGCHLD, &sa, NULL);

  pid = fork ();
  if (pid == 0) {
    pprintf ("I'm the child!\n");
    exit (0);
  }

  pprintf ("I'm the father\n");

  while (1) ;

  return 0;
}
