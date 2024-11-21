#define _GNU_SOURCE
#include <unistd.h>

#include "essayer.h"

struct param {
    void (*f)(void *);
    void *p;
    int d;
};

void aux (void *parametre) {
    struct param p = *(struct param *)parametre;
    alarm(p.d);
    p.f(p.p);
    alarm(0);
}

int
executer_avant_delai(void (*fun)(void *), void *parametre, int delai_en_seconde)
{
    struct param p;
    p.f = fun;
    p.p = parametre;
    p.d = delai_en_seconde;
    int r = essayer(aux, &p, SIGALRM);
    return r;
}
