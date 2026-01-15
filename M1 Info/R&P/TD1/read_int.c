#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char* endptr;
    strtol(argv[argc - 1], &endptr, 0);
    if (argc != 3 || *endptr != '\0') {
        fprintf(stderr, "ERROR : at least 3 arguments are needed, and the last one needs to be a number\n");
        exit(EXIT_FAILURE);
    }

    int file = open(argv[1], O_RDONLY);

    lseek(file, (atoi(argv[2]) - 1) * sizeof(int), SEEK_SET);

    int buf;
    read(file, &buf, sizeof(int));
    printf("%d\n", buf);

    close(file);

    return EXIT_SUCCESS;
}