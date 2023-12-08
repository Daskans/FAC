#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublelist.h"

/**
 * Définir la fonction createDoubleList prenant en paramètre un entier sizeOfContent strictement positif.
 * La fonction allouera dynamiquement une variable de type doubleList dont le tableau de caractère contient la chaine de caractère vide, mais pouvant contenir jusqu'à sizeOfContent caractères (en comptant le caractère de fin de chaine). Tous les champs doivent être alloués dynamiquement de manière à former une liste doublement chainée contenant un seul élément. La fonction renverra l'adresse de la  zone mémoire nouvellement allouée.
 * Traiter les cas d'erreur sévèrement.
 **/

/*
Define the function createDoubleList taking as parameter a strictly positive integer sizeOfContent.

The function will dynamically allocate a variable of type doubleList whose character array contains
the empty string, but can contain up to sizeOfContent characters (including the end character
of the string). All fields must be allocated dynamically so as to form a doubly linked list containing
a single element. The function will return the address of the newly allocated memory.

Handle error cases severely.
*/

doubleList* createDoubleList(unsigned int sizeOfContent){
}

/**
 * Définir la fonction createDoubleStack prenant en paramètre un entier sizeOfContent strictement positif.
 * La fonction allouera dynamiquement une variable de type doubleStack correspondant à une file à double entrée vide, mais dont les éléments seront en suite de taille sizeOfContent.
 * Traiter les cas d'erreur sévèrement.
 **/

/*
Define the function createDoubleStack taking as parameter a strictly positive integer sizeOfContent.

The function will dynamically allocate a variable of type doubleStack corresponding to an empty double
entry queue, but whose elements will be of sizeOfContent.

Handle error cases severely.
*/

doubleStack* createDoubleStack(unsigned int sizeOfContent){
}

/**
 * Définir la fonction freeDoubleStack prenant en paramètre l'adresse d'un doubleStack
 * et libérant la mémoire prise par cette variable, y compris l'ensemble de la mémoire occupée par la doubleList correspondante.
 * Attention à bien tout désallouer correctement. Comme d'habitude, votre fonction doit fonctionner même si la mémoire n'est que partiellement allouée.
 **/

/*
Define the function freeDoubleStack taking as parameter the address of a doubleStack
and freeing the memory taken by this variable, including all the memory occupied by the corresponding
doubleList.

Be careful to deallocate everything correctly. As usual, your function must work even if the memory
is only partially allocated.
*/

void freeDoubleStack(doubleStack* p) {
}


/**
 * Définir la fonction add prenant en paramètre l'adresse d'un doubleStack, une chaine de caractères content qui doit pouvoir être contenue dans une case de la pile à deux entrées, et une variable de type endPoint qui indiquera si l'on doit ajouter l'élément au début ou à la fin de la file.
 * La fonction devra ajouter un élément au début ou à la fin de la file contentant le contenu content.
 * Traiter les cas d'erreur sévèrement.
 * Vous avez le droit d'utiliser les fonctions de la bibliothèque string.h, notamment les fonctions strlen et strcpy.
**/

/*
Define the add function taking as parameters the address of a doubleStack, a string content
which must be contained in a cell of the stack with two entries, and a variable of type endPoint
which will indicate if we must add the element at the beginning or at the end of the queue.

The function must add an element at the beginning or at the end of the queue containing the content.

Handle error cases severely.

You are allowed to use the functions of the string.h library, especially the strlen and strcpy functions.
*/

void add(doubleStack* p, char* content, endPoint extremity)
{
}

/**
 * Définir la fonction printDoubleStack prenant en paramètre l'adresse d'un doubleStack et une variable de type endPoint qui indiquera si l'on doit parcourir la liste depuis le début ou depuis la fin.
 * La fonction devra afficher les contenus des éléments de la liste dans l'ordre indiqué, séparés par un espace, et terminer par un saut de ligne.
 * La fonction ne devra pas modifier la liste à deux entrées p.
 * Traiter les cas d'erreur sévèrement.
**/

/*
Define the function printDoubleStack taking as parameters the address of a doubleStack
and a variable of type endPoint which will indicate if we must browse the list from the beginning
or from the end.

The function must display the contents of the list elements in the indicated order, separated
by a space, and end with a line break.

The function must not modify the two-entry list p.

Handle error cases severely.
*/

void printDoubleStack(doubleStack* p, endPoint extremity)
{
}


/** Ecrire une fonction main qui attendra au moins un argument de l'utilisateur. 
 * Le premier argument correspond à un entier, qui indique la taille à reserver pour les éléments de la liste.
 * Les arguments suivants correspondront à des chaines de caractère.
 * Votre programme devra placer ces chaines de caractères dans une liste à deux entrée, la première par le début, la suivante par la fin, la suivante par le début, et ainsi de suite.
 * Une fois cela fait, votre programme affichera la liste, du début vers la fin.
 * Traiter les cas d'erreur sévèrement.
 **/

/*
Write a main function expecting at least one argument from the user. 

The first argument is an integer, which indicates the size to reserve for the elements of the list.

The following arguments are character strings.

Your program will have to store these strings in a two-entry list, the first one by the beginning,
the next one by the end, the next one by the beginning, and so on.

Once this is done, your program will display the list from the beginning to the end.

Handle error cases severely.
*/

int main(int argc,  char* argv[]) {
    doubleStack* stack; //keep the name stack as the double entry stack  //garder ce nom de variable pour stocker votre liste à deux entrées

    return EXIT_SUCCESS;
}