#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void System(char *s) {
    if (fork() ==0) {
        execl("/bin/sh", "blabla", "-c", s, NULL);
        perror("/bin/sh");
        exit(1);
    }
    wait(NULL);
}

void main() {
    System("echo bjr");
    System("sleep 2 ; echo bjr");
    System("ls -l");
}