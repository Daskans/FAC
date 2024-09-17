#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "error.h"

int main(int argc, char* argv[]) {
    check(argc==3,"il faut 3 arguments");
    int num = atoi(argv[2]);
    int len = log2((double)num) + 1;
    int bin[len];
    int w;
    FILE *file = fopen(argv[1],"w");
    check_syscall(w, "%s", argv[1]);
    for (int i = 0; i != len; i++) {
        printf("num = %d, num%2 = %d\n", num, num%2);
        bin[i] = num%2;
        num = num/2;
    }
    for (int i = 0; i < len; i++) {
        printf("bin[%d] = %d\n",i , bin[i]);
        fprintf(file, "%d", bin[len-1-i]);
    }
    printf("\n");
}