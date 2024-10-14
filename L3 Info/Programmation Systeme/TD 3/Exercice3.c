#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main (int argc, char* argv[]) {
    int tube[2];

    pipe(tube);
    // close(tube[1]); // <-- code bloqué si commenté avec read
    close(tube[0]);

    int i;
    // int r = read(tube[0], &i, 1);
    int r = write(tube[1], &i, 1);
    printf("%d\n", r);
    // ./Exercice3
    // echo $? 
    // renvoit 141
    // man 7 signal
    // dans le man faire /13
    // 13 -> SIGPIPE
    return EXIT_SUCCESS;
}
