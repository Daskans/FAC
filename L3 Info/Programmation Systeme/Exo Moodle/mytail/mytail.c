#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>

/* mode_t st_mode; -> File type and mode */
/* off_t st_size; -> Total size, in bytes */

/*  printf("Mode: %jo (octal)\n", (uintmax_t) filestat.st_mode); */
/* printf("File size: %jd bytes\n", (intmax_t) filestat.st_size); */

/* to test if the file is regular :

stat(pathname, &sb);
if ((sb.st_mode & S_IFMT) == S_IFREG) {
    // Handle regular file 
}
*/

int tailRegularFile(int inputFD, int outputFD, int numLines)
{
    int line = 0;
    int r;
    off_t pos;
    char c;
    read(inputFD, &c, sizeof(char));
    pos = lseek(inputFD, 0, SEEK_END);
    printf("bytes = %ld\n",pos*sizeof(pos));
    if (c == '\n') {
        line = -1;
    }
    while (line < numLines && pos != 0) {
        read(inputFD, &c, sizeof(char));
        if (c == '\n') {
            line++;
        }
        pos = lseek(inputFD, -2, SEEK_CUR);
    }
    if (line == 10) {
        lseek(inputFD, 2, SEEK_CUR);
    }
    while ((r = read(inputFD, &c, sizeof(char))) != 0) {
        write(outputFD, &c, sizeof(char));
        if (c == '\n') {
            printf("-->\n");
        }
    }
    return EXIT_SUCCESS;
}

int tailIregularFile(int inputFD, int outputFD, int numLines) {
    int tempfile = open("tempfile", O_CREAT | O_TRUNC | O_RDWR, 0640);
    int r;
    char c;
    while ((r = read(inputFD, &c, sizeof(char))) > 0) {
        write(tempfile, &c, sizeof(char));
    }
    tailRegularFile(inputFD, outputFD, numLines);
    close(tempfile);
    return EXIT_SUCCESS;
}

int tailFile(int inputFD, int outputFD, int numLines) {
    struct stat filestat;
    fstat(inputFD, &filestat);
    if ((filestat.st_mode & __S_IFMT) == __S_IFREG) {
        tailRegularFile(inputFD, outputFD, numLines);
    } else {
        tailIregularFile(inputFD, outputFD, numLines);
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    int fd = open("test", O_RDONLY);
    return tailFile(0, 1, 10);  
 }