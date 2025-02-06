#include "tools.h"

//
// TSP - BRUTE-FORCE
//
// -> la structure "point" est définie dans "tools.h"
// -> tsp_main peut être testé dès les 3 premières fonctions codées
//

double dist(point A, point B) {
    return hypot(B.x - A.x, B.y - A.y);
}

double value(point *V, int n, int *P) {
    double resultat = dist(V[P[0]], V[P[n - 1]]);
    for (int i = 0; i < (n - 1); i++) {
        resultat += dist(V[P[i]], V[P[i + 1]]);
    }
    return resultat;
}

double tsp_brute_force(point *V, int n, int *Q) {
    double w = DBL_MAX;
    int *Qtmp = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        Qtmp[i] = i;
    }
    do {
        double wtmp = value(V, n, Qtmp);
        if (w > wtmp) {
            w = wtmp;
            memcpy(Q, Qtmp, n * sizeof(int));
        }
        drawTour(V, n, Qtmp);
        SDL_Delay(500);
    } while (NextPermutation(Qtmp, n) && running);
    free(Qtmp);
    return w;
}

void MaxPermutation(int *P, int n, int k) {
    int i = n - 1;
    while (i > k && P[i - 1] > P[i]) {
        i--;
    }

    if (i == k) {
        return;
    }

    int j = n - 1;
    while (P[i - 1] > P[j]) {
        j--;
    }

    int tmp;
    SWAP(P[i - 1], P[j], tmp);

    int left = i;
    int right = n - 1;
    while (left < right) {
        SWAP(P[left], P[right], tmp);
        left++;
        right--;
    }
}

double value_opt(point *V, int n, int *P, double w) {
    double value_optimisation = dist(V[P[0]], V[P[1]]);
    for (int i = 2; i < n; i++) {
        value_optimisation += dist(V[P[i - 1]], V[P[i]]);
        double tmp = dist(V[P[i]], V[P[0]]);
        if (tmp > w) {
            return -i;
        }
    }
    return value_optimisation;
}

double tsp_brute_force_opt(point *V, int n, int *Q) {
    double w = DBL_MAX;
    int *Qtmp = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        Qtmp[i] = i;
    }
    for (int i = 0; (i < n) && running; i++) {
        double Wtmp = value_opt(V, (i + 1), Qtmp, w);
        if (w > Wtmp) {
            w = Wtmp;
            memcpy(Q, Qtmp, n * sizeof(int));
        }
        if (w <= Wtmp) {
            MaxPermutation(Qtmp, n, i);
        }
        drawTour(V, n, Qtmp);
        SDL_Delay(500);
    }
    free(Qtmp);
    return w;
}