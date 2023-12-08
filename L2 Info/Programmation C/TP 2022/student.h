#ifndef _DOUBLELIST
#define _DOUBLELIST


/*Définir les types structurés doubleList et doubleStack. 

Le type doubleList permettra d'implémenter des listes doublement chainées de chaines de caractères. Un élément de ce type devra donc contenir deux pointeurs, appelés "prev" et "next", vers les éléments suivant et précédent, et un pointeur "content" vers un tableau de caractères (char) alloué dynamiquement.

Le type doubleStack devra contenir des pointeurs vers les deux extrémités "start" et "end" d'une liste doublement chainée comme définie ci-dessus. Il devra également contenir un entier non signé "sizeOfContent".
*/


/* Define the structured types doubleList and doubleStack. 

The doubleList type will allow the implementation of doubly linked lists of strings.
An element of this type must contain two pointers, called "prev" and "next",
to the next and previous elements, and a "content" pointer to a dynamically allocated array
of characters (char).

The doubleStack type shall contain pointers to the two ends "start" and "end" of a doubly linked list
as defined above. It must also contain an unsigned integer "sizeOfContent".
 */


//DO NOT TOUCH !!!

typedef enum {
    START, END
}endPoint;

doubleList* createDoubleList(unsigned int sizeOfContent);
doubleStack* createDoubleStack(unsigned int sizeOfContent);
void freeDoubleStack();
void add(doubleStack* myStack, char* content, endPoint extremity);
char* pop(doubleStack* myStack, endPoint extremity);
unsigned int searchAndPop(doubleStack* myStack, char* toSearch, endPoint extremity);
void printDoubleStack(doubleStack* myStack, endPoint extremity);

// DO NOT TOUCH !!!

#endif