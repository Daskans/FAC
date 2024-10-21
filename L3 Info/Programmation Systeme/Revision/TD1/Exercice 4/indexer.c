#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "ERROR : ./indexer [filename]\n");
        return EXIT_FAILURE;
    }

    int r;
    char c;
    int input_file = open(argv[1], O_RDONLY);
    int output_file = open("file.idx", O_CREAT | O_TRUNC | O_WRONLY, 0642);

    off_t pos = lseek(input_file, 0, SEEK_SET);

    while ((r = read(input_file, &c, 1)) > 0) {
        if (c == '\n') {
            pos = lseek(input_file, 0, SEEK_CUR);
            write(output_file, &pos, sizeof(off_t));
        }
    }

    close(input_file);
    close(output_file);

    return EXIT_SUCCESS;
}