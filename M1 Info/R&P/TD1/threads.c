#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void* pthread_func(void* arg) {
    pthread_t id = pthread_self();

    char **array;
    array = (char**)arg;

    printf("%s, %d\n", array[0], atoi(array[1]));
    printf("Hello ! I'm thread n°%lu and I'm working correctly =D\n", (unsigned long)id);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        fprintf(stderr,"ERROR : needs 2 arguments ! %d were given\n",argc);
        exit(EXIT_FAILURE);
    }
    int num_threads = atoi(argv[1]);

    pthread_t threads[num_threads];
    for (int i = 0; i < num_threads; i++) {
        char *arg[2] = {"hello r!", "2"};
        pthread_create(&threads[i], NULL, pthread_func, &arg);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("ALL THREADS TERMINATED\n");

    return EXIT_SUCCESS;
}