// Écrire un programme contenant les fonctions suivantes~(sans utiliser de tableau ascii):
//    - bool isDigit(int c) qui vérifie si le caractère c est un chiffre (0 à 9). Cette fonction retourne true ou false suivant le cas.
//    - bool isLetter(int c) qui vérifie si le caractère c est une lettre (minuscule ou majuscule). Cette fonction retourne true ou false suivant le cas.
//    - int toCapital(int c) qui retourne la majuscule correspondant au caractère c (et laisse le caractère inchangé s'il ne s'agit pas d'une lettre minuscule).
//    - une fonction permettant de tester les précédentes. 

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool isDigit(int c) {
    if (0 <= c <= 9) return true;
    return false;
}

bool isLetter(int c) {
    if ('a' <= c <= 'z' || 'A' <= c <= 'Z') return true;
    return false;
}

int toCapital(int c) {
    int dif = 'a' - 'A';
    if ('a' <= c <= 'z') return c-dif;
    return c;
}

void main(void) {
    isDigit(4);
    isLetter('r');
    printf("%c\n",toCapital('r'));
}
