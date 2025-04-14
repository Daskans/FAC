#include "tp.h"
#include "htable.h"

//
// Paire de Points les Plus Proches
//
// Vous avez 5 fonctions à compléter: dist(), pppp_naive(), map(),
// pppp_random() et pppp_random2(). N'attendez pas la dernière minute pour
// les compiler et les tester.
//
// Chaque fonction du type pppp_xxx() doit renvoyer le couple {i,j}
// d'indices des deux points les plus proches.
//
// -> la structure "point" est définie dans "tools.h"
// -> la structure "couple" est définie dans "tp.h"
//

double dist(point A, point B) {
  return hypot((B.x - A.x), (B.y - A.y));
}

couple pppp_naive(point *V, int n) {
  couple result = {0, 1};
  double distMin = dist(V[0], V[1]);
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) {
        double distCurrent = dist(V[i], V[j]);
        if (distCurrent < distMin) {
          distMin = distCurrent;
          result.i = i;
          result.j = j;
          i = 0;
          break;
        }
      }
    }
  }
  
  return result;
}

// clang-format off

// map: N^2 -> N définit pour toute paire d'entiers (i,j) un entier
// unique. Il faut i,j >= 0. Il correspond à la somme des longueurs
// des diagonales montantes de la forme (t,0) -> (0,t), partant de
// (0,0), et jusqu'à atteindre le point (i,j) sans le compter. La
// longueur de la diagonale est le nombre de points qu'elle contient.
//
//       | | | | | |
//     4 .-.-.-.-.-.-
//       | | | | | |
//     3 o-.-.-.-.-.-
//       |\| | | | |
//     2 o-o-.-.-.-.-
//       |\|\| | | |
// j = 1 o-o-o-X-.-.-    Ex: map(i,j) = map(3,1) = (#o) = 11
//       |\|\|\|\| |
//     0 o-o-o-o-o-.-
//       0 1 2 3 4 5
//             i
//

// clang-format on

int map(int i, int j) {
  ;
  ;
  ;
  return 0;
}

// Point de vigilance. Attention à ce que les cellules voisines
// tombent dans le premier quadrant (i,j >= 0), sinon map(i,j) ne
// marchera pas.
couple pppp_random(point *V, int n) {
  couple result = {0, 1};
  double dmin = dist(V[0], V[1]);
  htable T = ht_create();
  for (int i = 0; i < n; i ++) {
    point Pt = V[i];
    double delta = dmin/sqrt(2);


  }
  return result;
}

// Version optimisée de pppp_random() comportant les deux extensions
// suivantes:
//
// . Il est possible de maintenir l'indice du dernier échec, disons tf
// (initialisée à -1), de sorte que les instructions (3b) et (3c)
// doivent être exécutée seulement si t>tf. Faire attention, lors
// d'un échec, de bien chercher le point q le plus proche dans le
// voisinage, sinon il y aura des échecs plusieurs fois au même
// indice.
//
// . Optimisez le nombre de cellules voisines en passant de 25 à 21
// cellules à explorer. Comparez.
//
couple pppp_random2(point *V, int n) {
  couple result = {-1, -1};
  ;
  ;
  ;
  return result;
}
