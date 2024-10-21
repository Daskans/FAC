#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/wait.h>

#define BUFFER_SIZE 4096

int tailRegular(int inputFD, int outputFD, int numLines) {
    off_t size = lseek(inputFD, 0, SEEK_END);
    if (size == -1) {
        fprintf(stderr, "Error read on the ending inputFD\n");
        return EXIT_FAILURE;
    }

    char c[BUFFER_SIZE];
    off_t pos = size;
    int lines_cpt = 0;
    int r;
    if (size > 0) {
        lseek(inputFD, size - 1, SEEK_SET);
        read(inputFD, c, 1);
        if (c[0] != '\n') {
            lines_cpt = 1;
        }
    }

    while (pos > 0 && lines_cpt <= numLines) {
        off_t block_size;
        if (pos >= BUFFER_SIZE) {
            block_size = BUFFER_SIZE;
        } else {
            block_size = pos;
        }
        pos = pos - block_size;
        lseek(inputFD, pos, SEEK_SET);
        r = read(inputFD, c, block_size);
        for (int i = r - 1; i >= 0; i--) {
            if (c[i] == '\n') {
                lines_cpt++;
                if (lines_cpt == numLines + 1) {
                    pos += i + 1;
                    break;
                }
            }
        }
    }

    // on place à la position trouvée
    lseek(inputFD, pos, SEEK_SET);

    // On écrit les données restantes sur la sortie
    while ((r = read(inputFD, c, BUFFER_SIZE)) > 0) {
        write(outputFD, c, r);
    }

    return 0;
}
