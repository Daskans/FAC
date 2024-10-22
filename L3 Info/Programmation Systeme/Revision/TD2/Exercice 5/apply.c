#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <fnmatch.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "ERROR : ./execute [command] {optional arg list} [motif]\n");
        return EXIT_FAILURE;
    }

    //argv[argc-1] = NULL;

    DIR *dir = opendir("*");
    
    //execvp(argv[1], argv + 1);

    return EXIT_SUCCESS;;
}