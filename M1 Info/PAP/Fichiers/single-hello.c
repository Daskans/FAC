#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>


const char *bonjour[]={ "Good morning",
			"Bonjour",
			"Buon Giorno",
			"Buenos días",
			"Egun on",
			NULL};

const char *aurevoir[]={"Bye",
			"Au revoir",
			"Arrivederci",
			"Hasta luego",
			"Adio",
			NULL};
  
int main()
{
#pragma omp parallel  
  {
#pragma omp single
#pragma omp task
    {
      for (int i = 0 ; bonjour[i] != NULL; i++)  
	printf("%s (%d)\n",bonjour[i], omp_get_thread_num());
#pragma omp taskwait
#pragma omp task
      for (int i = 0 ; aurevoir[i] != NULL; i++)  
	printf("%s (%d)\n",aurevoir[i], omp_get_thread_num());
    }
  }
  return 0;
}
