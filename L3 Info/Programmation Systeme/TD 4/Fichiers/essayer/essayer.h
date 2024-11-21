#ifndef ESSAYER_H
#define ESSAYER_H

#include <stdio.h>
#include <stdlib.h>

#include <signal.h>

int essayer(void  (*f)(void*), void *p, int sig);

#endif
