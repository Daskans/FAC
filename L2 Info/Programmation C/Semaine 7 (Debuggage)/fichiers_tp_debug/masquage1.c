#include <stdio.h>
#include <stdlib.h>

int main(void){
  int x = 3;
  printf("%d\n",x);
  {
    int x = 17;
    printf("%d\n",x);
  }
  printf("%d\n",x);
  return EXIT_SUCCESS;
}