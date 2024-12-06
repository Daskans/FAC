
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void *thread_func (void *arg)
{
  printf ("%s from thread!\n", (char *)arg);

  return NULL;
}

int main (int argc, char *argv[])
{
  pthread_t pid;

  pthread_create (&pid, NULL, thread_func, "Hello");

  thread_func ("Hello from main");

  pthread_join (pid, NULL);

  return 0;
}
