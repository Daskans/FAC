#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "error.h"

int main(int argc, char* argv[]) {
    check(argc==2,"il faut 2 arguments");
    char c;
    int r;
    int num = 0;
    int len = 0;
    int result = 0;
    int in = open(argv[1], O_RDONLY);
    while((r = read(in, &c, 1)) != 0) {
        len++;
    }
    lseek(in, 0, SEEK_SET);
    int i = 0;
    while((r = read(in, &c, 1)) != 0) {
        num = (&c)[0] - '0';
        result += pow((num*2),len-1-i);
        printf("num = %d, len = %d, i = %d, result = %d\n",num, len, i, result);
        i++;
    }
    printf("result = %d\n",result);
    close(in);
    
}