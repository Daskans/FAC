#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel
    #pragma omp single
    {
        printf("Bonjour from %d\n", omp_get_thread_num());
        printf("Au revoir from %d\n", omp_get_thread_num());
    }

    return 0;
}
