#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

int main (int argc, char *argv[])
{
  pid_t pid;

  pid = fork ();
  if (pid) { // father
    int status;

    kill (pid, SIGSEGV);
    
    wait (&status);

    if (WIFSIGNALED(status)) {
      int sig = WTERMSIG(status);
      pprintf ("Child killed by signal %d (%s)\n", sig, strsignal (sig));
    } else {
      pprintf ("Child exited normally (code: %d)\n", WEXITSTATUS (status));
    }

  } else { // Child
    pprintf ("Child start\n");
    
    // SIGABRT
    //
    // SIGINT
    //raise (SIGINT);
    //
    // SIGALRM
    //alarm (1);
    //
    // SIGSEGV
    //((int *)NULL)[0] = 12;
    //
    // SIGFPE
    //int i = 1, j = 0;
    //printf ("div = %d\n", i / j);
    // SIGPIPE
#if 0
    int tube[2];
    pipe (tube);
    close (tube[0]);
    write (tube[1], "abc", 3);
#endif
    sleep(2);

    pprintf ("Child end\n");
  }

  return 0;
}
