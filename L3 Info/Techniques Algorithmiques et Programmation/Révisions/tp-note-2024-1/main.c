#include "tools.h"
#include "tp.h"


graph createGraph(int n) {
  graph G;
  G.n    = n;
  G.deg  = malloc(n * sizeof(*(G.deg)));
  G.list = malloc(n * sizeof(*(G.list)));
  for (int u = 0; u < n; u++)
    G.list[u] = malloc(n * sizeof(int)); // taille n par défaut
  G.deg[0] = -1; // par défaut, G ne sera pas dessiné par drawGraph()
  return G;
}


void freeGraph(graph G) {
  for (int u = 0; u < G.n; u++)
    free(G.list[u]);
  free(G.list);
  free(G.deg);
}


int main(int argc, char *argv[]) {

  int n = (argc >= 2) ? atoi(argv[1]) : 10;
  unsigned seed = time(NULL) % 1000;
  printf("seed: %u\n", seed); // pour rejouer la même chose au cas où
  srandom(seed);

  TopChrono(0);                  // initialise tous les chronos
  point *V = generatePoints(n);  // n points au hasard

  init_SDL_OpenGL();    // initialisation avant de dessiner
  drawTour(V, n, NULL); // dessine seulement les points

  printf("*** closest pair of points ***\n");
  if (n < 2) {
    printf("Error: n=%d, it must be at least two.\n", n);
    exit(1);
  }                                   // ici n>=2
  
#define PPPP(algo)                                                \
  {                                                               \
    TopChrono(1);                                                 \
    couple C = pppp_ ## algo(V, n);                               \
    printf("pppp_" # algo "():\tdist(V[%i],V[%i]) = ", C.i, C.j); \
    if (C.i < 0 || C.i >= n || C.j < 0 || C.j >= n || C.i == C.j) \
    printf("\xf0\x9f\x94\xa5 fail!");                             \
    else {                                                        \
      printf("%.04lf", dist(V[C.i], V[C.j]));                     \
      M.list[C.i][M.deg[C.i]++] = C.j;                            \
      M.list[C.j][M.deg[C.j]++] = C.i;                            \
    }                                                             \
    printf("  (time=%s)\n", TopChrono(1));                        \
  }

  running = true;                         // force l'exécution
  bool redraw = true;                     // si les points ont changés
  graph M = createGraph(n);               // graphe vide (ensemble d'arête)
  update = true;                          // force l'affichage
  while (running) {                       // affiche le résultat et attend (q
                                          // pour sortir)
    if (redraw) {                         // recalcule si nécessaire
      bzero(M.deg, M.n*sizeof(*M.deg));   // vide le graphe
      PPPP(naive);
      PPPP(random);
      PPPP(random2);
      printf("\n");
    }
    drawGraph(V, n, NULL, M);             // dessine le graphe (ensemble d'arêtes)
    redraw = handleEvent(update);         // attend un évènement (=true) ou pas
  }

  printf("\n");
  freeGraph(M);
  TopChrono(-1);
  free(V);
  cleaning_SDL_OpenGL();

  return 0;
}
