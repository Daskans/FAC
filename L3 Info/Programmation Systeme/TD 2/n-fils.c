#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("ERROR : not enough argument");
        return(EXIT_FAILURE);
    }
    for (int i = 0; i < atoi(argv[1]); i++) {
        pid_t pid = fork();

        if (pid == 0) {
            printf("je suis %d, le fils %d de %d\n", getpid(), i ,getppid());
            exit(0);
        }
        wait(NULL);
    }
}