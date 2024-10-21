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
    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    while ((r = fread(&c, 1, sizeof(c), input_file)) > 0) {
        fwrite(&c, 1, sizeof(c), output_file);
    }
    fclose(input_file);
    fclose(output_file);
    return EXIT_SUCCESS;
}