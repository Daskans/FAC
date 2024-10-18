#define XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>

#define NSIGNORT 32

struct sigaction tout;

int emetteur(int pere, int argc, char * argv[]) {
  int k = atoi(argv[1]);

  sleep(1); 

  for(int i = 0 ; i < k ; i++) 
    for(int j = 2; j < argc; j++){
      kill(pere,atoi(argv[j]));
  }

  //kill(pere,9);
  return 0;
}

void traitant_reception(int s) {
  static int occ[32];
  printf("%d - %d\n", ++occ[s], s);
}

int recepteur(int fils) {
  printf("récepteur : %d\n", getpid());

  struct sigaction a;
  a.sa_handler = traitant_reception;
  a.sa_flags = SA_RESETHAND;
  sigemptyset(&a.sa_mask);
  //sigaction(SIGINT, &a, NULL);

  // installation du handler pour tous les signaux non RT  

  for(int sig = 0 ; sig < NSIGNORT ; sig++) {
    sigaction( sig, &a, NULL);
  }
  //printf("%d\n",sig);
  sigprocmask(SIG_UNBLOCK, &tout, NULL);
    
  while(1) 
    pause();
  
  return 0;
}


int main(int argc, char *argv[]){
  sigfillset(&tout);
  sigprocmask(SIG_BLOCK, &tout, NULL);
  pid_t pid = fork();  
  if (pid == 0)
    emetteur(getppid(),argc,argv);
  else
    recepteur(pid);  
}
