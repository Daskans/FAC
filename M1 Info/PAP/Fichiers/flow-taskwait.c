#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fa ()
{
  sleep(1);
  return 2;
}

int fb ()
{
  sleep (1);
  return 3;
}

int fc ()
{
  sleep (2);
  return 4;
}

int fadd (int i, int j)
{
  sleep (1);
  return i + j;
}

int fmul (int i, int j)
{
  sleep (1);
  return i * j;
}

int main ()
{
  int a, b, c, d, e;
#pragma omp parallel
#pragma omp single
  {
    #pragma omp task shared (a)
    a = fa ();

    #pragma omp task shared (b)
    b = fb ();

    #pragma omp task shared (c)
    c = fc ();

    #pragma omp taskwait

    #pragma omp task shared (d)
    d = fadd (a, b);

    #pragma omp taskwait

    #pragma omp task shared (e)
    e = fmul (c, d);
  }

  printf ("result = %d\n", e);
  
  return EXIT_SUCCESS;
}
