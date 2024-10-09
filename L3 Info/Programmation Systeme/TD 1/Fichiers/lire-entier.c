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
    check(argc==3,"./lire-entier [filename] [position]");
    int log = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
    dup2(log, STDERR_FILENO);
    off_t num;
    int r;
    int in = open(argv[1], O_RDONLY);
    check_syscall(in, "%s", argv[1]);
    off_t pos = lseek(in, atoi(argv[2]), SEEK_SET);
    if ((r = read(in, &num, sizeof(num))) != 0) {
        check_syscall(r, "read");
        printf("%d\n", num);
        //write(1, &num, sizeof(num));
    }
    close(log);
    close(in);
    
}