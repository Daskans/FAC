#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int 
main()
{
    #pragma omp parallel
    {
    int i;

    #pragma omp for schedule(guided, 1)
        for(i=0; i < 100; i++)
        {
            usleep(100);
            printf("%d traite %i\n", omp_get_thread_num(), i);
        }    
            

    }
    return 0;
}
