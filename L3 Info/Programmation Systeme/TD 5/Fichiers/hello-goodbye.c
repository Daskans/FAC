#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *HelloGoodbye(void *p)
{
    printf("%p: bonjour\n", pthread_self()); 
    sleep(1);
    printf("%p: a bientot\n", pthread_self()); 

    return NULL;
}

int main(int argc, char *argv[])
{
    
    pthread_t pid;
    HelloGoodbye(NULL);

    return EXIT_SUCCESS;
}
