/*
 * Dans cet exercice vous allez implémenter un nombre de primitives permettant
 * de manipuler des nombres complexes.
 * Complétez ensuite la fonction main pour tester ces primitives.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#ifndef M_PI
#define M_PI   3.14159265358979323846   /* pi */
#endif /*M_PI*/


struct complex {
  double imaginary;
  double real;
};
#include "complex.h"

//Returns a reference to a complex_t memory space with the real part equal to a and imaginary part equal to b
complex_t * new_complex(double a, double b){
    complex_t * p_c = (complex_t *) malloc(sizeof(complex_t));
    if(p_c == NULL){
        fprintf(stderr,"Not enough memory");
        exit(EXIT_FAILURE);
    }
    p_c->imaginary = a;
    p_c->real = b;
    return p_c;
}

//Returns the real part of the complex pointed by c
double get_real(complex_t * p_c){
    if(p_c==NULL){
        exit(EXIT_FAILURE);
    }
    return p_c->real;
}

//Returns the imaginary part of the complex pointed by p_c
//TO DO
double get_imaginary(complex_t *p_c){
    if(p_c==NULL){
        exit(EXIT_FAILURE);
    }
    return p_c->imaginary;
}

//Returns the modulus of the complex pointed by p_c
//TO DO
double get_modulo(complex_t *p_c){
    if(p_c==NULL){
        exit(EXIT_FAILURE);
    }
    double mod = sqrt(pow(p_c->real,2)+pow(p_c->imaginary,2));
    return mod;
}

//Returns the argument of the complex pointed by p_c
//TO DO
double get_argument(complex_t *p_c){
    if(p_c==NULL){
        exit(EXIT_FAILURE);
    }
    return -M_PI+atan2(p_c->imaginary,p_c->real);
}

//Sets the real part of the complex number referenced by p_c without changing it's imaginary part
//TO DO
void set_real(complex_t * p_c, double value) {
    if (p_c==NULL) {
        exit(EXIT_FAILURE);
    }
    p_c->real = value;
}

//Sets the imaginary part of the complex number referenced by p_c without changing it's real part
//TO DO
void set_imaginary(complex_t * p_c, double value){
    p_c->imaginary = value;
}

//Sets the modulo part of the complex number referenced by p_c without changing it's argument part
//TO DO
void set_modulo(complex_t * p_c, double value) {
    if (p_c==NULL) {
        exit(EXIT_FAILURE);
    }
    double mod = get_modulo(p_c);
    set_real(p_c, get_real(p_c)*value/mod);
    set_imaginary(p_c, get_imaginary(p_c)*value/mod);
}



//Sets the argument part of the complex number referenced by p_c without changing it's modulo part
//TO DO
void set_argument(complex_t * p_c, double value){
    if(p_c==NULL){
        exit(EXIT_FAILURE);
    }
    double modulo=get_modulo(p_c);
    set_real(p_c,modulo*cos(value));
    set_imaginary(p_c,modulo*sin(value));
}

//Display the complex pointed by p_c in the following format real +img i
//Examples:
//2.00 + 6.00i
//TO DO
void display_complex(complex_t *p_c){
    if(p_c==NULL){
        printf("complex donnée incorrect\n");
    }
    else{
        printf("%2lf+%2lfi\n",get_real(p_c),get_imaginary(p_c));
    }
}



//Returns True if the complex pointed by p_c1 and the complex pointed by p_c2 are equal, False otherwise
//TO DO
bool equal_complex(complex_t *p_c1, complex_t *p_c2){
    if(p_c1==NULL || p_c2==NULL){
        return false;
    }
    else if(get_real(p_c1)==get_real(p_c2) && get_imaginary(p_c1)==get_imaginary(p_c2)){
        return true;
    }
    else{
        return false;
    }
}

//Computes the complex pointed by conjugate  as the conjugate of the complex pointed by p_c
//TO DO
void conjugate_complex(complex_t *p_c, complex_t *conjugate){
    if(p_c==NULL){
        exit(EXIT_FAILURE);
    }
    conjugate->real=get_real(p_c);
    conjugate->imaginary=-(get_imaginary(p_c));
}

//Computes the complex pointed by res as the sum of the complex pointed by p_c1 and the complex pointed by p_c2
//TO DO
void addition_complex(complex_t *p_c1, complex_t *p_c2, complex_t *res){
    if(p_c1==NULL || p_c2==NULL){
        exit(EXIT_FAILURE);
    }
    res->real=get_real(p_c1)+get_real(p_c2);
    res->imaginary=get_imaginary(p_c1)+get_imaginary(p_c2);
}

//Computes the complex pointed by res as the multiplication of the complex pointed by p_c1 and the complex pointed by p_c2
//TO DO
void multiplication_complex(complex_t *p_c1, complex_t *p_c2, complex_t *res){
    if(p_c1==NULL || p_c2==NULL){
        exit(EXIT_FAILURE);
    }
    res->real=(get_real(p_c1)*get_real(p_c2)-get_imaginary(p_c1)*get_imaginary(p_c2));
    res->imaginary=(get_real(p_c1)*get_imaginary(p_c2)+get_imaginary(p_c1)*get_real(p_c2));
}


int main() {
    complex_t * p_c1 = new_complex(0, 0);
    set_real(p_c1,1.0);
    set_imaginary(p_c1,3.5);
    printf("p_c1 : %lf + i %lf\n", get_real(p_c1),get_imaginary(p_c1));
    printf("p_c1 : (%lf, %lf)\n", get_modulo(p_c1),get_argument(p_c1));
    
    complex_t * p_c2 = new_complex(5, 4);
    set_modulo(p_c2,2.4);
    set_argument(p_c2,3.1);
    printf("p_c2 : %lf + i %lf\n", get_real(p_c2),get_imaginary(p_c2));
    printf("p_c2 : (%lf, %lf)\n", get_modulo(p_c2),get_argument(p_c2));
    
    complex_t * res = new_complex(0, 0);
    addition_complex(p_c1,p_c2,res);
    printf("res_add : %lf + i %lf\n", get_real(res),get_imaginary(res));
    printf("res_add : (%lf, %lf)\n", get_modulo(res),get_argument(res));
    
    multiplication_complex(p_c1,p_c2,res);
    printf("res_mul : %lf + i %lf\n", get_real(res),get_imaginary(res));
    printf("res_mul : (%lf, %lf)\n", get_modulo(res),get_argument(res));
    
    return EXIT_SUCCESS;
}

