#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "distributeur.h"

const unsigned long MAX = 100 * 1000;

distributeur_t d;

void *for_en_parallele(void *p)
{
  for(unsigned long i=0; i < MAX; i++)
    distributeur_suivant(d);
  return NULL;
}

int 
main(int argc, char *argv[])
{

  int n = atoi(argv[1]);
  pthread_t tids[n];
  d = distributeur_new();

  for(int i = 0; i <n ; i++)
    pthread_create(tids + i, NULL, for_en_parallele, NULL);

  for(int i = 0; i <n ; i++)
    pthread_join(tids[i],NULL);

  printf("%d\n",distributeur_valeur(d));

  return EXIT_SUCCESS;
}
