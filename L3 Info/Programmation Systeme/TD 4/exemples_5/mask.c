#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void really_sleep (unsigned secs)
{
  do {
    secs = sleep (secs);
    //printf ("sleep returned %d\n", secs);
  } while (secs > 0);
}

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

void my_sig_handler (int sig)
{
  pprintf ("I received signal %s, but I don't care\n", strsignal (sig));
}

int main (int argc, char *argv[])
{
  struct sigaction sa;

  sa.sa_flags = SA_RESTART;
  sigemptyset (&sa.sa_mask);
  sa.sa_handler = my_sig_handler;

  sigaction (SIGINT, &sa, NULL);

  // TODO: mask SIGINT

  pprintf ("Any ^C will be postponed\n");

  really_sleep (5);
  
  // TODO: unmask SIGINT

  pprintf ("^C are allowed again\n");

  really_sleep (5);

  pprintf ("End of program\n");

  return 0;
}
