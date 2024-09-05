#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

#include "error.h"

int main(int argc, char **argv)
{
    char c;
    int r, w;
    check(argc == 2, "il faut deux arguments");
    int out = open(argv[1],O_CREAT | O_WRONLY | O_TRUNC, 0640);
    check_syscall(out, "%s", argv[1]);

    while ((r = read(0, &c, 1)) != 0) {
        check_syscall(r, "read");

        w = write(1, &c, 1);
        check_syscall(w, "write");

        w = write(out, &c, 1);
        check_syscall(w, "write out");
    }
    int end = close(out);
    check_syscall(end, "close");

    return EXIT_SUCCESS;
}
