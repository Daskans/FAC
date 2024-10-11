#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>

#include "error.h"

int main(int argc, char* argv[]) {

    int tube[2];

    pipe(tube);

    if (fork()) {
        dup2(tube[1], STDOUT_FILENO);
        close(tube[0]);
        close(tube[1]);
        execvp(argv[2], argv+2);
        perror("ERROR fork");
        exit(STDOUT_FILENO);
    }
    dup2(tube[0], STDIN_FILENO);
    close(tube[0]);
    close(tube[1]);
    execlp("tee", "tee", argv[1], NULL); // 2x tee important, on construit argv 
    perror("ERROR");
    exit(STDOUT_FILENO);

    return EXIT_SUCCESS;

}

/*

|
pipe
|
fork ----------------
|                   |
exec tee            exec ls
open()              readdir       
read()              fstat
write()             print
write()             fstat
*/