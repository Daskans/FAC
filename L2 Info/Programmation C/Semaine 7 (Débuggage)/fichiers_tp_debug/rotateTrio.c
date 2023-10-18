#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int x,y,z;
}trio;

void rotateLeft(int *a, int *b, int *c){
  int *tmp = a;
  *a = *b;
  *b = *c;
  *c = *tmp;
}

int main(int argc, char* argv[]){

  trio tr = {1,2,3};
  printf("Initialisation des champs d'un trio: ");
  printf("%d %d %d\n", tr.x,tr.y,tr.z);
  rotateLeft(&(tr.x),&(tr.y),&(tr.z));
  printf("Contenu du trio suite a une rotation a gauche: ");
  printf("%d %d %d\n", tr.x,tr.y,tr.z);
  return EXIT_SUCCESS;
}