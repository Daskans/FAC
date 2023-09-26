#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;

void str_count(char *s, uint *c) {
    for (; *s!='\0'; s++) {
        (*c)++;
        printf("test %d\n",*c);
    }
}

void main(void){
    char *tab="hello";
    uint count=0;
    str_count(tab, &count);
    printf("%d\n", count);
}