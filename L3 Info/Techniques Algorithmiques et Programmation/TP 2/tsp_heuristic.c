#include "tools.h"
#include "tsp_brute_force.h"

//
//  TSP - HEURISTIQUES
//

void reverse(int *T, int p, int q) {
  // Renverse la partie T[p]...T[q] du tableau T avec p<q si
  // T={0,1,2,3,4,5,6} et p=2 et q=5, alors le nouveau tableau T sera
  // {0,1, 5,4,3,2, 6}.
  int tmp;
  for (int i = p, j = q; i < j; i++, j--) {
    SWAP(T[i], T[j], tmp);
  }
  return;
}

double first_flip(point *V, int n, int *P) {
    // Renvoie le gain>0 du premier flip réalisable, tout en réalisant
    // le flip, et 0 s'il n'y en a pas.
    for (int i = 0; i < n; i++) {
        for (int j = i + 2; j < n; j++) {
            double gain = (dist(V[P[i]], V[P[i+1]]) + dist(V[P[j]], V[P[j+1]])) - 
                          (dist(V[P[i]], V[P[j]]) + dist(V[P[i+1]], V[P[j+1]]));
            if (gain > 0) {
                reverse(P, i + 1, j);
                return gain;
            }
            
        }
    }
    return 0.0;
}

double tsp_flip(point *V, int n, int *P) {
    // La fonction doit renvoyer la valeur de la tournée obtenue. Pensez
    // à initialiser P, par exemple à P[i]=i. Pensez aussi faire
    // drawTour() pour visualiser chaque flip.
    for (int i = 0; i < n; i++) {
        P[i] = i;
    }
    double tour = 0.0;
    for (int i = 0; i < n; i++) {
        tour += dist(V[P[i]], V[P[(i + 1) % n]]);
    }
    double gain = first_flip(V, n, P);
    while (gain > 0.0 && running) {
        gain = first_flip(V, n, P);
        tour -= gain;
        drawTour(V, n, P);
    }
    return tour;
}

double tsp_greedy(point *V, int n, int *P) {
    // La fonction doit renvoyer la valeur de la tournée obtenue. Pensez
    // à initialiser P, par exemple à P[i]=i.
    for (int i = 0; i < n; i++) {
        P[i] = i;
    }
    double tour = 0.0;
    for (int i = 0; i < n; i++) {
        tour += dist(V[P[i]], V[P[(i + 1) % n]]);
    }
    for (int i = 0; i < n; i++) {
        double min = DBL_MAX;
        int index = -1;
        for (int j = i + 1; j < n; j++) {
            double tmp = dist(V[P[i]], V[P[j]]);
            if (tmp < min) {
                min = tmp;
                index = j;
            }
        }
        if (index != -1) {
            int tmp = P[i + 1];
            P[i + 1] = P[index];
            P[index] = tmp;
        }
        tour += min;
    }
    return 0.0;
}
