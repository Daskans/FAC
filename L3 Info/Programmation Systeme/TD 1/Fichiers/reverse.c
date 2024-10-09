#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>

#include "error.h"

#define SUFFIXE ".rev"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("./reverse [filename]");
    }

    char *filename = argv[1];

    int l = strlen(filename);
    char rev_filename[l + strlen(SUFFIXE) + 1];
    strncpy(rev_filename, argv[1], l);
    strcpy(rev_filename + l, SUFFIXE);

    int file = open(filename, O_RDONLY);
    check_syscall(file, "%s", filename);
    int rev = open(rev_filename, O_CREAT | O_WRONLY | O_TRUNC, 0640);
    check_syscall(rev, "%s", rev_filename);

    off_t len = lseek (file, 0, SEEK_END);

    char *jsp = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);

    //for (int i = 0; i < len; i++) {
    //}

    return EXIT_SUCCESS;
}