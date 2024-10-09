#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        getchar();
        printf("je suis %d, le fils de %d\n", getpid(), getppid());
        exit(0);
    }
    //wait(NULL);
    printf("je suis %d, le pere de %d\n", getpid(), pid);
    return(0);
}