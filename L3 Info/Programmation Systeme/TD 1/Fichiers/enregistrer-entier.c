#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "error.h"

#define SUFFIXE ".bin"

int main(int argc, char* argv[]) {

    check(argc==4,"./enregistrer-entier [filename] [position] [number]");

    int l = strlen(argv[1]);
    char bin_filename[l + strlen(SUFFIXE) + 1];
    strncpy(bin_filename, argv[1], l);
    strcpy(bin_filename + l, SUFFIXE);

    int out = open(bin_filename, O_CREAT | O_WRONLY | O_TRUNC, 0640);
    check_syscall(out, "%s", argv[1]);

    off_t pos = lseek(out, atoi(argv[2]), SEEK_SET);

    off_t num = atoi(argv[3]);
    printf("%d\n",num);
    ssize_t w;

    w = write(out, &num, sizeof(num));
    check_syscall(w, "write");

    close(out);

    return EXIT_SUCCESS;
}