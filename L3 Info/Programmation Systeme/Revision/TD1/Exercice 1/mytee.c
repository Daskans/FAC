#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "ERROR : ./mytee [output_file_name]\n");
        return EXIT_SUCCESS;
    }
    int r;
    char c;
    int output = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0642);
    while ((r = read(STDIN_FILENO, &c, 1)) > 0) {
        write(STDOUT_FILENO, &c, 1);
        write(output, &c, 1);

    }
    return EXIT_SUCCESS;
}