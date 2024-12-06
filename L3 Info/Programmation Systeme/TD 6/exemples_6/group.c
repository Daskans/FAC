
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NBTHREADS = 4;

void *thread_func (void *arg)
{
  int me = (int)(intptr_t)arg;

  printf ("Hello from thread %d\n", me);

  return NULL;
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    NBTHREADS = atoi (argv[1]);

  // TODO: create threads
  pthread_t pid[NBTHREADS];
  
  for (int i = 0; i < NBTHREADS; i++)
    pthread_create (pid + i, NULL, thread_func, (void *)(intptr_t)i);

  // TODO: wait for threads
  for (int i = 0; i < NBTHREADS; i++)
    pthread_join (pid[i], NULL);

  return 0;
}
