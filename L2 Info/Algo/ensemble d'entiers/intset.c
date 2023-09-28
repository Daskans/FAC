/*
 * Dans cet exercice vous allez implementer un nombre de primitives et de
 * fonctions utilitaires permettant de manipuler des ensembles d'entiers positifs
 * dans un intervalle [min, max].
 * Completez egalement la fonction main qui vous est fournie afin de tester
 * vos fonctions.
 *
 * Les fonctions d'allocation, de liberation de la memoire, de
 * generation aleatoire et d'affichage des ensembles vous sont donnees.
 *
 * Un ensemble sera implemente comme un tableaux de booleans, comme suit :
 * set[0] correspond a l'element min
 * set[max-min] correspond a l'element max
 * ...
 * la valeur True dans le tableau indique la presence de l'element dans l'ensemble
 * la valeur False indique l'absence
 
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdbool.h>
#include "intset.h"

struct intset{
  bool *set;
  unsigned int min, max;
};

/*
 The following functions are given
*/

/*
 Allocates memory for a set of integers in the interval [min, max]
 */
static intset_t* allocate_set (unsigned int min, unsigned int max)
{
    if (min > max){
        fprintf(stderr, "max should be bigger than min!\n");
        exit(EXIT_FAILURE);
    }
    intset_t* s = (intset_t *)malloc(sizeof(intset_t));
    if (!s){
        fprintf(stderr, "Not enough memory!\n");
        exit(EXIT_FAILURE);
    }
    s->set = (bool *) malloc((max-min+1)*sizeof(bool));
    if (!s->set){
        fprintf(stderr, "Not enough memory!\n");
        exit(EXIT_FAILURE);
    }
    s->min = min;
    s->max = max;
    return s;
}

/*
 Frees the memory allocated for an intset
 */
void free_set (intset_t *s)
{
    if (s) free(s->set);
    free(s);
}

/*
 Generates an empty set of positive integers in the interval [min, max]
 */
intset_t* generate_empty_set (unsigned int min, unsigned int max)
{
    unsigned int i;
    intset_t* s = allocate_set(min, max);
    for(i = 0; i <= (max-min); ++i) {
        s->set[i] = false;
    }
    return s;
}

/*
 Generates randomly a set of n positive integers in the interval [min, max]
 */
intset_t* generate_set (unsigned int min, unsigned int max, unsigned int n){
    unsigned int i, elem;
    
    intset_t* s = generate_empty_set(min, max);
    
    i= 0;
    while (i < n){
        elem = rand()%(max-min+1);
        if (!s->set[elem]){
            i++;
            s->set[elem] = true;
        }
    }
    return s;
}

/*
 The primitives to be implemented
*/

/*
 Tests whether an element is part of the set
 */
//TO DO
bool is_in(intset_t* s, unsigned int elem);

/*
 Adds an element to the set
 */
//TO DO
void add(intset_t* s, unsigned int elem);

/*
 Deletes an element from the set
 */
 //TO DO
void delete(intset_t* s, unsigned int elem);

/*
 Utilitary functions to implement
*/

/*
 Returns the number of elements of the set
 */
//TO DO
unsigned int nb_elements(intset_t* s);

/*
 Empties a set
 */
//TO DO
void empty_set(intset_t* s);

/*
 Prints a set in the interval [min, max]
 */
 //TO DO
void print_set (intset_t* s);

/*
 Computes and outputs the union of two sets
 */
//TO DO
intset_t* union_set(intset_t* s1, intset_t* s2);

/*
 Computes and outputs the intersection of two sets
 */
 //TO DO
intset_t* intersection(intset_t* s1, intset_t* s2);

/*
 Computes and outputs the difference of two sets
 */
//TO DO
intset_t* difference(intset_t* s1, intset_t* s2);


int main()
{
    unsigned int min1 = 0, max1 = 30;
    unsigned int min2 = 10, max2 = 100;
    
    //On cree 2 ensembles dans les intervalles donnes
    unsigned int n1 = 10, n2 = 30;
    srand(time(0));
    intset_t* s1 = generate_set(min1, max1, n1);
    intset_t* s2 = generate_set(min2, max2, n2);
    
    //On affiche les 2 ensembles
    printf("\nPremier ensemble généré");
    print_set(s1);
    printf("\nDeuxième ensemble généré");
    print_set(s2);
    
    intset_t* x = union_set(s1, s2);
    printf("\ns1 U s2=");
    print_set(x);
    printf("\n|s1 U s2|=%d\n",nb_elements(x));
    free_set(x);
    
    x = intersection(s1, s2);
    printf("\ns1 intersect s2=");
    print_set(x);
    printf("\n|s1 intersect s2|=%d\n",nb_elements(x));
    free_set(x);
    
    x = difference(s1, s2);
    printf("\ns1 \\ s2=");
    print_set(x);
    printf("\n|s1 \\ s2|=%d\n",nb_elements(x));
    free_set(x);
    
    //On libere la memoire de ces deux ensembles
    free_set(s1);
    free_set(s2);
    
    return EXIT_SUCCESS;
}
