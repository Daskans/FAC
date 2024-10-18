#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

void my_sig_handler (int sig)
{
  pprintf ("I received signal %s, but I don't care\n", strsignal (sig));
}

void really_sleep (unsigned secs)
{
  do {
    secs = sleep (secs);
    //printf ("sleep returned %d\n", secs);
  } while (secs > 0);
}

int main (int argc, char *argv[])
{
  struct sigaction sa, old;

  sa.sa_flags = SA_RESTART;
  sigemptyset (&sa.sa_mask);
  sa.sa_handler = my_sig_handler;

  sigaction (SIGINT, &sa, &old);

  printf ("I'll be immune to ^C for 5 secs\n");

  really_sleep (5);

  // TODO: restore standard behavior for SIGINT

  sa.sa_handler = SIG_DFL;

  sigaction (SIGINT, &sa, NULL);

  printf ("I fear ^C again!\n");

  really_sleep (5);

  printf ("End of program\n");

  return 0;
}
