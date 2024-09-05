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
     check(argc == 3, "il faut 3 arguments");
     int in = open(argv[1], O_RDONLY);
     check_syscall(in, "%s", argv[1]);
     int out = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0640);
     check_syscall(out, "%s", argv[2]);

     while((r = read(in, &c, 1)) != 0) {
          check_syscall(r, "read");
          int w = write(out, &c, 1);
          check_syscall(w, "write");
     }
     close(in);
     close(out);
     return EXIT_SUCCESS;
}
