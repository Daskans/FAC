#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void display_list(double *tab, int n) {
    printf("[ ");
    for (int i=0; i<n; i++) printf("%lf ", tab[i]);
    printf("]\n");
}

bool summean1(double *tab, int n, double *var1, double *var2) {
    if (tab == NULL || n==0 || var1 == NULL || var2 == NULL) return false;
    double sum = 0;
    double avg;
    for (int i=0; i<n; i++) {
        sum += tab[i];
    }
    avg = sum/n;
    *var1 = sum;
    *var2 = avg;
    return true;
}

bool summean2(double *tab, int n, double *tabVar) {
    if (tab == NULL || n==0 ||tabVar == NULL) return false;
    double sum = 0;
    double avg;
    for (int i=0; i<n; i++) {
        sum += tab[i];
    }
    avg = sum/n;
    tabVar[0] = sum;
    tabVar[1] = avg;
    return true;
}

void main(void) {
    int n = 5;
    double tab[5] = {1, 2, 3, 4, 5.0};
    double var1;
    double var2;
    double tabVar[2];
    //for (int i=0; i<n; i++) tab[i] = i;
    summean1(tab, n, &var1, &var2);
    summean2(tab, n, tabVar);
    display_list(tab, n);
    display_list(tabVar, 2);
    //printf("var1 = %lf\nvar2 = %lf\n", var1, var2);
    
}