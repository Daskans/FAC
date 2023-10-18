#include <stdio.h>
#include <stdlib.h>

void init (int *p, int n){
    for (int i=0; i<n; i++)
        p[i] = i;
    free (p);
}

int main()
{
    int *pTab = (int*)malloc(sizeof(int)*10);
    
    if (pTab)
        init(pTab, 10);
    
    free(pTab);
    
    return 0;
}