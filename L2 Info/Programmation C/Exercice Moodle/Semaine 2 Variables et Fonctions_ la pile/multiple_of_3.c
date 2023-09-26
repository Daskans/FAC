#include <stdlib.h>
#include <stdio.h>

//Écrire une fonction count_multiple_of_3 qui calcule et renvoie le nombre d'éléments multiples de 3 d'un tableau d'entiers positifs. 
//Par exemple, pour le tableau [ 3 1 5 9 4 6 ], la fonction devra renvoyer 3. Si le tableau est de taille nulle, 
//la fonction devra renvoyer un code d'erreur adapté de votre choix qui ne doit pas limiter les cas d'appels de la fonction.

//Écrire une fonction display_multiple_of_3  qui affiche les éléments multiples de 3 d'un tableau d'entiers positifs.. 
//Par exemple, pour le tableau [ 3 1 5 9 4 6 ], la fonction devra afficher [ 3 9 6 ].

//En utilisant les fonctions précédemment définies, écrire une fonction main qui affiche les éléments multiples de 3, 
//et leur nombre total, du tableau [ 3 1 5 6 4 9 ] puis du tableau [ 6 2 1 6 ].

int count_multiple_of_3(int* tab, int n) {
    int count = 0;
    for (int i=0; i<n; i++) {
        if (tab[i]%3==0) {
            count++;
        }
    }
    return count;
}

void display_multiple_of_3(int* tab, int n) {
    printf("[ ");
    for (int i=0; i<n; i++) {
        if (tab[i]%3==0) {
            printf("%d ",tab[i]);
        }
    }
    printf("]\n");
}

void main(void) {
    int n=6;
    int tab[]={3,1,5,9,4,6};
    count_multiple_of_3(tab,n);
    display_multiple_of_3(tab,n);
}