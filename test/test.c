#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

void print_char_tab(char *tab) {
    printf("[ ");
    for (uint i = 0; tab[i]!=0; i++) {
        printf("%c ", tab[i]);
    }
    printf("]");
}

void main(void) {
    char *tab1 = "abc";
    char *tab2 = "def";
    tab2[2] = tab1;
    print_char_tab(tab2);
}