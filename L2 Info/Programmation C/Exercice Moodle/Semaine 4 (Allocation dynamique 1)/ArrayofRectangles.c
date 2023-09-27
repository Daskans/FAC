// -Ecrire une fonction createArrayofRectangles qui alloue 
//  un tableau de taille size (passée en paramètre) pouvant 
//  contenir des éléments de type struct rectangle sachant 

//  typedef struct rectangle{
//	    unsigned int width;
//	    unsigned int height;
// } 

// -Votre fonction devra retourner la l'adresse de la première case allouée.
// -Ecrire une fonction permettant de libérer ce tableau. 
//  Votre fonction, comme la fonction free, 
//  ne devra pas planter même si le tableau n'a pas pu être créé correctement
// -Ecrivez une fonction main permettant de tester votre programme   

#include <stdlib.h>
#include <stdio.h>

typedef struct rectangle{
    unsigned int width;
    unsigned int height;
} rectangle_t;

typedef unsigned int uint;

int* createArrayofRectangles(rectangle_t r, int size) {
    
}