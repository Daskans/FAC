#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <asm-generic/signal-defs.h>


void stop(int s) {
    a.sa_handler = SIG_DFL;
    a.sa_flags = 0;
    sigemptyset(&a.sa_mask);
    printf(" ctrl-c\n");
    sigaction(SIGINT, &a, NULL);
}

int main(int argc, char* argv[]) {
    
    struct sigaction a;
    
    a.sa_handler = stop;
    a.sa_flags = 0;
    sigemptyset(&a.sa_mask);

    sigaction(SIGINT, &a, NULL);

    for(;;) {
        pause();
    }
    return EXIT_SUCCESS;
}