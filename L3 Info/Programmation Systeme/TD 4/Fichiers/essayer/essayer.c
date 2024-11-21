#define _GNU_SOURCE
#include "essayer.h"

#include <assert.h>
#include <signal.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>

sigjmp_buf my_buf;
typedef void (*func_t)(void);

void traitant(int s) {
    siglongjmp(my_buf, s);
}

int essayer(void  (*f)(void*), void *p, int sig)
{
    int res;
    jmp_buf oldj;
    *oldj = *my_buf;
    struct sigaction a, old;
    a.sa_handler = traitant;
    a.sa_flags = SA_RESTART;
    sigemptyset(&a.sa_mask);

    sigaction(sig, &a, &old);
    if ((res = sigsetjmp(my_buf, 1)) == 0) {
        f(p);
    }
    sigaction(sig, &old, NULL);*
    my_buf = *oldj;
    if (res == 0 || res == sig) {
        return res;
    }

    raise(res);

    return res;
}
