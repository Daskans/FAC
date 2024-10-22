#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "ERROR : ./execute [command] {param list}\n");
        return EXIT_FAILURE;
    }

    execvp(argv[1], argv + 1);

    return EXIT_SUCCESS;;
}