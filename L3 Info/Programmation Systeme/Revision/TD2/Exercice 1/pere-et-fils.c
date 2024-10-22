#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        printf("hello je suis %d, le fils de %d\n", getpid(), getppid());
    } else {
        printf("hello je suis %d, le pere de %d\n", getpid(), pid);
    }

    return EXIT_SUCCESS;
}