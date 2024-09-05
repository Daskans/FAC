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
     FILE *in = fopen(argv[1], "r");
     //check_syscall(in, "%s", argv[1]);
     FILE *out = fopen(argv[2], "w");
     //check_syscall(out, "%s", argv[2]);

     while((r = fread(&c, sizeof(c), 1, in)) != 0) {
          check_syscall(r, "read");
          int w = fwrite(&c, sizeof(c), 1, out);
          check_syscall(w, "write");
     }
     fclose(in);
     fclose(out);
     return EXIT_SUCCESS;
}
