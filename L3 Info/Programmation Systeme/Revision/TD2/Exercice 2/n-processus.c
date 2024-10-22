#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "ERROR : ./n-processus [num]\n");
    }

    int num = atoi(argv[1]);

    pid_t pid;

    for (int i = 0; i < num; i++) {
        pid = fork();
        if (pid == 0) {
            printf("PROCESSUS %d\n", getpid());
            exit(EXIT_SUCCESS);
        }
    }

    return EXIT_SUCCESS;
}