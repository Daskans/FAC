#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

int main(int argc, char *argv[]) {
    int tube[2];
    if (pipe(tube) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    int cmd1_status, cmd2_status;

    if (pid == 0) { // child -> cmd1
        close(tube[0]);

        if (dup2(tube[1], STDOUT_FILENO) == -1) {
            perror("dup STDOUT");
            exit(EXIT_FAILURE);
        }
        close(tube[1]);

        execl("/bin/sh", "sh", "-c", argv[1], NULL);
        perror("cmd1");
        exit(EXIT_FAILURE);
    } else { // parent -> cmd2
        close(tube[1]);

        if (dup2(tube[0], STDIN_FILENO) == -1) {
            perror("dup STDIN");
            exit(EXIT_FAILURE);
        }
        close(tube[0]);

        wait(&cmd1_status);
        execvp(argv[2], argv + 2);
        perror("cmd2");
        exit(EXIT_FAILURE);
    }

    wait(&cmd2_status);
    if (WIFEXITED(cmd1_status)) {
        return cmd1_status;
    }

    close(tube[0]);
    close(tube[1]);

    return cmd2_status;
}