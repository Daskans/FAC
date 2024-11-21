#define _XOPEN_SOURCE 600

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_barrier_t barrier;


void *HelloGoodbye(void *p)
{
    int id = p;
    printf("%d: bonjour\n", id); 
    //sleep(1);
    pthread_barrier_wait(&barrier);
    printf("%d: a bientot\n", id);
    return NULL;
}

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);
    pthread_t pid[num];
    pthread_barrier_init(&barrier, NULL, num);
    if (argc != 2) {
        fprintf(stderr, "ERROR : ./hello-goodbye [num]");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < num; i++) {
        pthread_create (&pid[i], NULL, HelloGoodbye, i);
    }

    for (int i = 0; i < num; i++) {
        pthread_join(pid[i], NULL);
    }

    return EXIT_SUCCESS;
}
