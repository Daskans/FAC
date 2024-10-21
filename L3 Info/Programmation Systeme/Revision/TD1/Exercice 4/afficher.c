#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "ERROR : ./afficher [filename] [line_number]\n");
        return EXIT_FAILURE;
    }

    char c;
    int r;
    int i = atoi(argv[2]) ;
    int file = open(argv[1], O_RDONLY);
    int file_idx = open("file.idx", O_RDONLY);
    off_t start_pos;

    
    off_t idx_pos = lseek(file_idx, (i - 1)* sizeof(off_t), SEEK_SET);
    read(file_idx, &start_pos, sizeof(off_t));
    start_pos = lseek(file, start_pos, SEEK_SET);

    if (i = 0) {
        start_pos = lseek(file, 0, SEEK_SET);
    }

    while(r = read(file, &c, 1)) {
        if (r <= 0 || c == '\n') {
            break;
        }
        write(STDOUT_FILENO, &c, 1);
    }

    if (c = '\n') {
        write(STDOUT_FILENO, &c, 1);
    }

    close(file);
    close(file_idx);

    return EXIT_SUCCESS;
}