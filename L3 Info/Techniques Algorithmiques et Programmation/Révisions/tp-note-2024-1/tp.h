#ifndef __TP_H__
#define __TP_H__

#include "tools.h" // pour la structure de point

// Un couple d'indices
typedef struct{
  int i,j;
} couple;

// Distance euclidienne entre deux points.
double dist(point A, point B);

// Algorithme selon la méthode naïve en O(n^2).
// Il s'agit d'examiner toutes les paires de points possibles.
// Suppose qu'il y a au moins n >= 2 points dans V.
couple pppp_naive(point* V, int n);


// Algorithme probabiliste en O(n) en moyenne.
// Il s'agit de l'algorithme vu en TD, cf. aussi section 5.2.6 du cours.
// Suppose qu'il y a au moins n >= 2 points dans V.
couple pppp_random(point* V, int n);
couple pppp_random2(point* V, int n); // version optimisée

#endif
