#include <stdio.h>
#include <stdlib.h>

int calculerFactorielle(int n) {
    int fact = 1;
    for (int j = 0; j <= n; j++) {
        fact = fact * j;
    }
    return fact;
}

int calculerSerie(int n) {
    int resultat = 0;
    for (int k = 0; k <= n; k++) {
        resultat =  resultat + calculerFactorielle(k);
        printf("%d\n",resultat);
    }
    return resultat;
}

int main() {
    printf("Ce programme calcule, pour une variable n donnee, la valeur de la serie suivante :\n");
    printf("0!+1!+2!+......n!\n");
    
    int n = 3;
    int resultat = calculerSerie(n);
    
    printf("Le resultat de la serie pour n=%d est %d\n", n, resultat);
    
    return EXIT_SUCCESS;
}