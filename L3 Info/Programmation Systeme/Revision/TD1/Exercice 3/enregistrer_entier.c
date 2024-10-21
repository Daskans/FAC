#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFERSIZE 64

int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "ERROR : ./enregistrer-entier [filename] [position] [value]\n");
        return EXIT_FAILURE;
    }

    char bin_filename[sizeof(".bin") + sizeof(argv[1])];
    strcat(bin_filename, argv[1]);
    strcat(bin_filename, ".bin");

    off_t value = atoi(argv[3]);
    int file = open(bin_filename, O_CREAT | O_TRUNC | O_WRONLY, 0642);

    lseek(file, atoi(argv[2]), SEEK_SET);

    write(file, &value, (BUFFERSIZE/8));

    close(file);

    return EXIT_SUCCESS;
}