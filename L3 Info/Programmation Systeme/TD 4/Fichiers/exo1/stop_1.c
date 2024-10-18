#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <asm-generic/signal-defs.h>


int counter = 0;

void stop(int s) {
    printf(" ctrl-c\n");
    counter+;
}

int main(int argc, char* argv[]) {
    
    struct sigaction a;
    
    a.sa_handler = stop;
    a.sa_flags = 0;
    sigemptyset(&a.sa_mask);

    sigaction(SIGINT, &a, NULL);

    for(;;) {
        if (counter == 1) {
            a.sa_handler = SIG_DFL;
            sigaction(SIGINT, &a, NULL);
        }
        pause();
    }
    return EXIT_SUCCESS;
}