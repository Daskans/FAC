#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>


void rediriger_vers(char *filename, void (*f)(void)) {

    int file = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0642);
    int backup = dup(STDOUT_FILENO);
    dup2(file, STDOUT_FILENO);
    close(file);

    f();

    dup2(backup, STDOUT_FILENO);
    close(backup);

}

void fun(void) {
    printf("fdp pourquoi tu marche pas\nslurp\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "ERROR : ./lire-entier [filename]\n");
        return EXIT_FAILURE;
    }
    printf("début\n");

    rediriger_vers(argv[1], fun);

    printf("fin\n");

    return EXIT_SUCCESS;
}