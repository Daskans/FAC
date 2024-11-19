#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

typedef struct distributeur *distributeur_t;
extern distributeur_t distributeur_new();
extern int distributeur_suivant(distributeur_t d);
extern int distributeur_valeur(distributeur_t d);
extern void raz(distributeur_t d);

#endif