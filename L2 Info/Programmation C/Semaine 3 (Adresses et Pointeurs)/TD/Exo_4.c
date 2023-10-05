#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int g1(int *p, int i, int n) {
    assert(i>=0 && i<n);
    return *(p+i);
}

int* g2(int *p, int i, int n) {
    assert(i>=0 && i<n);
    return (p+i);
}

void g3(int *p, int n) {
    int *q=p;
    for (int i=0; i<n; i++, q++) {
        printf("%d\t%d\t%d\n", i, q[0], *q, *(p+i));
    }
}

void g4(char *s) {
    for (; *s!='\0'; s++) {
        printf("%c\t%c\n", s, *s, s[0]);
    }
}

void main(void) {
    int tab1[]={1,2,3,4,5,6};
    char *tab2="hello";
    int n=6;
    printf("%d\n",g1(tab1,0,n));
    printf("%d\n",*g2(tab1,3,n));
    g3(tab1,n);
    g4(tab2);
}