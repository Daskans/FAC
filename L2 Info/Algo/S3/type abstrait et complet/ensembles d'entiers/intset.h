
#ifndef INTSET_H
#define INTSET_H

typedef struct intset intset_t;

/*
 Frees the memory allocated for an intset
 */
extern void free_set (intset_t *s);

/*
 Generates an empty set of positive integers in the interval [min, max]
 */
extern intset_t* generate_empty_set (unsigned int min, unsigned int max);

/*
 Generates randomly a set of n positive integers in the interval [min, max]
 */
extern intset_t* generate_set (unsigned int min, unsigned int max, unsigned int n);


/*
Primitives to implement
*/

/*
 Tests whether an element is part of the set
 */
extern bool is_in(intset_t* s, unsigned int elem);

/*
 Adds an element to the set
 */
extern void add(intset_t* s, unsigned int elem);

/*
 Deletes an element from the set
 */
extern void delete(intset_t* s, unsigned int elem);

/*
 Utilitary functions to implement
*/

/*
 Returns the number of elements of the set
 */
extern unsigned int nb_elements(intset_t* s);

/*
 Empties a set
 */
extern void empty_set(intset_t* s);

/*
 Prints a set in the interval [min, max]
 */
extern void print_set (intset_t* s);

/*
 Computes and outputs the union of two sets
 */
extern intset_t* union_set(intset_t* s1, intset_t* s2);

/*
 Computes and outputs the intersection of two sets
 */
extern intset_t* intersection(intset_t* s1, intset_t* s2);

/*
 Computes and outputs the difference of two sets
 */
extern intset_t* difference(intset_t* s1, intset_t* s2);

#endif /* INTSET_H */
