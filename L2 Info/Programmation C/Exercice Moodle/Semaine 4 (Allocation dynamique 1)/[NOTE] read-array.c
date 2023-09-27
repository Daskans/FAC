//Ecrire un programme qui lit les entiers passés en paramètre 
//et qui les mémorise dans l'ordre inverse d'apparition 
//dans un tableau nommé tab en réservant dynamiquement 
//l'emplacement en mémoire pour les stocker.

//Exemples :

//$>./a.out 1 2 3 4 5
//tab = [ 5, 4, 3, 2, 1 ]


//$>./a.out 3 9 7
//tab = [ 7, 9, 3 ]

//Penser à fournir une fonction d'usage.


#include <stdlib.h>
#include <stdio.h>

static void usage(char * command) {
    fprintf(stderr,"%s <integer array size> \n", command);
    exit(EXIT_FAILURE);
}

int main(int argc, char*argv[]) {
    if (argc<2) {
        usage(argv[0]);
    }
    
    int* tab;
    int size=argc-1;
    tab = (int*) malloc(size * sizeof(int*));
    if (tab==NULL) {
        fprintf(stderr,"not enough memory");
        return EXIT_FAILURE;
    }

    for (int i=size; i>0; i--) {
        tab[size-i]=atoi(argv[i]);
    }

    printf("tab = [ %d",tab[0]);
    for (int i=1; i<size; i++) {
        printf(", %d",tab[i]);
    }

    printf(" ]");
    free(tab);
    tab=NULL;
    return EXIT_SUCCESS;
}