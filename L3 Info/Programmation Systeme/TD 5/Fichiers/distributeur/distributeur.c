#include "distributeur.h"
#include <stdlib.h>

struct distributeur
{
    int indice;
};

distributeur_t distributeur_new() {
    return calloc(1, sizeof(struct distributeur));
}

int distributeur_suivant(distributeur_t d)
{
    return d->indice++;

}


int distributeur_valeur(distributeur_t d)
{
    return d->indice;
}


void raz(distributeur_t d)
{
    d->indice = 0;
}