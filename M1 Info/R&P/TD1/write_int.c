#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "ERROR : needs at least 2 arguments");
        exit(EXIT_FAILURE);
    }
    int num_array[argc-2];
    for (int i = 0; i < argc - 2; i ++) {
        num_array[i] = atoi(argv[i + 2]);
    }

    int file = open(argv[1], O_CREAT | O_TRUNC | O_RDWR);

    //for (int i = 0; i < argc - 2; i ++)
    {
        write(file, num_array, (argc - 2) * sizeof(int));
    }

    close(file);

    return EXIT_SUCCESS;
}