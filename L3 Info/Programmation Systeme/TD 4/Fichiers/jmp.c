#include <stdio.h>

#include <setjmp.h>
#include <signal.h>

void f(jmp_buf my_buf, int val) {
    longjmp(my_buf, val);
}

int g(jmp_buf my_buf) {
    return setjmp(my_buf);
}

int main (int argc, char *argv[]) {
    volatile int i = 0;
    jmp_buf my_buf;
    int r = g (my_buf);
    printf("%d\n", i);
    i++;
    if (i < 10) {
        f(my_buf, 1);
    }

    return 0;
}