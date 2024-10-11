#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main (int argc, char* argv[]) {
    int tube[2];

    pipe(tube);

    for (int i=1;;i++){
        write(tube[1], &i, 1);
        // printf(" %d", i); // dernier nombres : 65508 65509 655
        printf(" %d\n", i); // dernier nombre : 65536 -> 64 ko −> 2^16
        // un tube stock 64 ko, il peut être bloqué en écriture
    }

    return EXIT_SUCCESS;
}
