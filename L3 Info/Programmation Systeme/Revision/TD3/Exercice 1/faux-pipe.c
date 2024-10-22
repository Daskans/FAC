#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>


int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "ERROR : ./faux-pipe.c [cmd1] [cmd2] {arg list}\n");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        int temp_file = open("temp_file", O_CREAT | O_TRUNC | O_WRONLY, 0644);
        if (temp_file == -1) {
            perror("temp_file writing mode");
            exit(EXIT_FAILURE);
        }

        if (dup2(temp_file, STDOUT_FILENO) == -1) {
            perror("dup2 STDOUT parent");
            exit(EXIT_FAILURE);
        }
        close(temp_file);

        execl("/bin/sh", "sh", "-c", argv[1], NULL);
        perror("exec cmd1");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);

        int temp_file = open("temp_file", O_RDONLY);
        if (temp_file == -1) {
            perror("temp_file reading mode");
            exit(EXIT_FAILURE);
        }

        pid_t pid2 = fork();
        if (pid2 == 0) {
            if (dup2(temp_file, STDIN_FILENO) == -1) {
                perror("dup2 STDIN child");
                exit(EXIT_FAILURE);
            }
            close(temp_file);

            execvp(argv[2], argv + 2);
            perror("exec cmd2");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
    }


    return EXIT_SUCCESS;
}