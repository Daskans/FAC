#include <stdio.h>
#include <stdlib.h>


#define SIZE 9

/*
 * Recherche la position de la première occurence d'un élément dans un
 * tableau trié du plus petit au plus grand. Si l'élément n'existe pas, il
 * renvoie la taille du tableau.
 *
 * Paramètres:
 *  - tableau - un tableau trié du plus petit au plus grand
 *  - size - la taille du tableau
 *  - value - la valeur a cherché dans le tableau
 * Retour:
 *  Un entier entre 0 et size inclu.
 */
int dichotomic_search( int* tableau, int size, int value ) {
    int begin = 0;
    int end = size;
    int milieu;
    while( begin <= end ){
        milieu = (begin + end)/2;
        if( tableau[milieu]>=value ){
            end = milieu;
        }else{
            begin = milieu;
        }
    }
    if( tableau[begin] == value ){
        return begin;
    }else{
        return size;
    }
}


int main( void){
    
    int size = SIZE;
    int tableau[ SIZE ] = {1,1,2,3,6,6,8,9,11};
    
    int element = 6;
    int id = dichotomic_search( tableau, size, element );
    if( id == size ){
        printf("Element %d are not in the array.\n", element );
    }else{
        printf("First position of %d : %d\n", element, id );	
    }
}
