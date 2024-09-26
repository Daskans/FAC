#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "error.h"

int main(int argc, char* argv[]) {
    check(argc==4,"il faut 4 arguments");
    int num = atoi(argv[3]);
    ssize_t w;
    char *c = (char *)&num;
    int out = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0640);
    off_t pos = lseek(out, atoi(argv[2]), SEEK_SET);
    check_syscall(out, "%s", argv[1]);
    int byte_written = 0;
    while (byte_written < sizeof(num)) {
        w = write(out, &c[byte_written], 1);
        check_syscall(w, "write");
        if (w != 1) {
            perror("ERROR : error in writing in file");
            close(out);
            exit(EXIT_FAILURE);
        }
        byte_written++;
    }
    close(out);
    return EXIT_SUCCESS;
}