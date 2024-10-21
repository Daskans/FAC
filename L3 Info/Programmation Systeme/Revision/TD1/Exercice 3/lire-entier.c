#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFERSIZE 64

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "ERROR : ./lire-entier [filename] [position]\n");
        return EXIT_FAILURE;
    }

    off_t value;
    int file = open(argv[1], O_RDONLY);

    lseek(file, atoi(argv[2]), SEEK_SET);

    read(file, &value, (BUFFERSIZE/8));
    printf("%ld\n", value);

    close(file);

    return EXIT_SUCCESS;
}