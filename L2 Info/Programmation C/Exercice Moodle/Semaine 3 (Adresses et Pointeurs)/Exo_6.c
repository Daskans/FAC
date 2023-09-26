#include <stdlib.h>
#include <stdio.h>
#define N 5

int main(void) {
    int a=1, b=2, c=3;
    int tab[N];
    for (int i=0; i<N; i++) {
        tab[i] = N-i;
    }
    *(tab + tab[a + *(tab + b)]) += *(tab + a);
    c-=tab[tab[*(tab + b)]];
    tab[*(tab+b-*(tab+4))-*(tab+c)]=tab[0];

    for (int i=0; i<N; i++) {
        printf("%d", tab[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}