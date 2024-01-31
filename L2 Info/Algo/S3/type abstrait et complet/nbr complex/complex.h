#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct complex complex_t;

//Returns a reference to a complex_t memory space with the real part equal to a and imaginary part equal to b
extern complex_t * new_complex(double a, double b);

//Returns the real part of the complex pointed by p_c
extern double get_real(complex_t *p_c);

//Returns the imaginary part of the complex pointed by p_c
extern double get_imaginary(complex_t *p_c);

//Returns the modulus of the complex pointed by p_c
extern double get_modulo(complex_t *p_c);

//Returns the argument of the complex pointed by p_c
extern double get_argument(complex_t *p_c);

//Sets the real part of the complex number referenced by p_c without changing it's imaginary part
extern void set_real(complex_t * p_c, double value);

//Sets the imaginary part of the complex number referenced by p_c without changing it's real part
extern void set_imaginary(complex_t * p_c, double value);

//Sets the modulo part of the complex number referenced by p_c without changing it's argument part
extern void set_modulo(complex_t * p_c, double value);

//Sets the argument part of the complex number referenced by p_c without changing it's modulo part
extern void set_argument(complex_t * p_c, double value);

//Display the complex pointed by p_c in the following format real +img i
//Examples:
//2.00 + 6.00i
//TO DO
extern void display_complex(complex_t *p_c);

//Returns True if the complex pointed by p_c1 and the complex pointed by p_c2 are equal, False otherwise
extern bool equal_complex(complex_t *p_c1, complex_t *p_c2);

//Computes the complex pointed by conjugate  as the conjugate of the complex pointed by p_c
extern void conjugate_complex(complex_t *p_c, complex_t *conjugate);

//Computes the complex pointed by res as the sum of the complex pointed by p_c1 and the complex pointed by p_c2
extern void addition_complex(complex_t *p_c1, complex_t *p_c2, complex_t *res);

//Computes the complex pointed by res as the multiplication of the complex pointed by p_c1 and the complex pointed by p_c2
extern void multiplication_complex(complex_t *p_c1, complex_t *p_c2, complex_t *res);

#endif /* COMPLEX_H */
