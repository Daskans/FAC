#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "ERROR : ./mycopy [intput_file_name] [output_file_name]\n");
        return EXIT_SUCCESS;
    }

    int r;
    char c;
    int input_file = open(argv[1], O_RDONLY);
    int output_file = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0642);

    while ((r = read(input_file, &c, 1)) > 0) {
        write(output_file, &c, 1);
    }
    close(input_file);
    close(output_file);
    return EXIT_SUCCESS;
}