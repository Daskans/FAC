#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <asm-generic/signal-defs.h>


void stop(int s) {
    printf(" ctrl-c\n");
}

int main(int argc, char* argv[]) {
    
    struct sigaction a;
    
    a.sa_handler = stop;
    a.sa_flags = SA_RESETHAND;
    sigemptyset(&a.sa_mask);

    sigaction(SIGINT, &a, NULL);

    for(;;) {
        pause();
    }
    return EXIT_SUCCESS;
}