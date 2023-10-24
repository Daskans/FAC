#include <stdio.h>
#include <stdlib.h>

#define BOLDRED   "\033[1m\033[31m" 
#define RESET     "\033[0m" -

typedef unsigned int uint;

void print_char_tab(char *tab) {
    printf("[ ");
    for (uint i = 0; tab[i]!=0; i++) {
        printf("%c ", tab[i]);
    }
    printf("]");
}

void main(void) {
    char str_value = '0' + 2;
    char str[2];
    str[0] = str_value;
    str[1] = '\0';
    printf("%s%s%s\n", BOLDRED, str, RESET);
}