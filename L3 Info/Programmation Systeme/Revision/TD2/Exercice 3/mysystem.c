#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


void System(char *command) {
    if (fork() == 0) {
        execl("/bin/sh", "blabla", "-c", command, NULL);
        perror("/bin/sh");
        exit(EXIT_SUCCESS);
    }
    wait(NULL);
}

int main(int argc, char *argv[]) {
    { System("echo bonjour"); System("echo au revoir"); }
    printf("---=============---\n");
    { if (!fork()) exit(0); System("sleep 1 ; echo bonjour") ; System("echo au revoir"); }
    wait(NULL);
    return EXIT_SUCCESS;
}