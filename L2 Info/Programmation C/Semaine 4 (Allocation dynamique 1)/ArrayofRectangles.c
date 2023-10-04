// -Ecrire une fonction createArrayofRectangles qui alloue 
//  un tableau de taille size (passée en paramètre) pouvant 
//  contenir des éléments de type struct rectangle sachant 

//  typedef struct rectangle{
//	    unsigned int width;
//	    unsigned int height;
// } 

// -Votre fonction devra retourner l'adresse de la première case allouée.
// -Ecrire une fonction permettant de libérer ce tableau. 
//  Votre fonction, comme la fonction free, 
//  ne devra pas planter même si le tableau n'a pas pu être créé correctement
// -Ecrivez une fonction main permettant de tester votre programme   

#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;

typedef struct rectangle{
    uint width;
    uint height;
} rectangle_t;

rectangle_t* createArrayofRectangles(int size) {
    rectangle_t* tab;
    tab = (rectangle_t*) malloc(size*sizeof(rectangle_t*));
    if (tab==NULL) {
        fprintf(stderr,"not enough memory");
        exit(EXIT_FAILURE);
    }
    return tab;
}

int free_rectangle(rectangle_t* t) {
    if (t==NULL) {
        fprintf(stderr,"argument is not valid");
        return EXIT_FAILURE;
    }
    free(t);
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    rectangle_t *tab = createArrayofRectangles(10);
    free_rectangle(tab);
    return EXIT_SUCCESS;
}