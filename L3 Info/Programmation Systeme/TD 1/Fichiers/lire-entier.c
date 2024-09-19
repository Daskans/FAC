#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "error.h"

#define BUFFERSIZE 64

char *filename = "ERREURS-LIRE.log";

int main(int argc, char* argv[]) {
    check(argc==3,"il faut 3 arguments");
    int log = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
    dup2(log, STDERR_FILENO);
    char c[BUFFERSIZE];
    int r, w;
    int in = open(argv[1], O_RDONLY);
    check_syscall(in, "%s", argv[1]);
    off_t pos = lseek(in, atoi(argv[2]), SEEK_SET);
    while((r = read(in, c, BUFFERSIZE)) != 0) {
        check_syscall(r, "read");
        for (int i = 0; i < r; i++) {
            printf("%d ", c[i]);
        }
        //w = write(STDOUT_FILENO, c, r);
        check_syscall(w, "write");
    }
    
    close(in);
    
}