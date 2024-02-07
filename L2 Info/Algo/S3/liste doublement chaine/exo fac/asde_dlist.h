/*
* This file is a copy of the orginal.
* Modification will not be taken into account.
*/

#ifndef ASDE_DLIST_H
#define ASDE_DLIST_H

#include <stdbool.h>

typedef struct DCell DCell;
typedef DCell * DList;

// returns an empty list
extern DList asde_dlist_create_empty(void);

// tests whether a DList is empty
extern bool asde_dlist_isEmpty(DList L);

// gets next element in a DList ->  fonction suivant(val L:liste d'objet): liste d'objet;
extern  DList  asde_dlist_next(DList L);

// gets previous element in a DList ->  fonction precedent(val L:liste d'objet): liste d'objet;
extern  DList  asde_dlist_prev(DList L);

// gets data in a SList ->  fonction valeur(val L:liste d'objet): objet;
extern  int asde_dlist_data(DList L);

//adds a new element on the start of the list -> fonction insereEnTete(val L: liste d'objet, val x objet): liste d'objet;
extern DList asde_dlist_prepend(DList L, int data);

// -> fonction supprimerEnTete(val L: liste d'objet): liste d'objet;
extern DList asde_dlist_delete_first(DList L);

// -> fonction insererApres(val L:liste d'objets, val p : liste d'objets, val x: objet): liste d'objet;
extern DList asde_dlist_insert_after(DList L, DList p, int data);

// -> fonction supprimerApres(val L:liste d'objets, val p : liste d'objets): liste d'objet;
extern DList asde_dlist_delete_after(DList L, DList p);

// -> fonction insererAvant(val L:liste d'objets, val p : liste d'objets, val x: objet): liste d'objet;
extern DList asde_dlist_insert_before(DList L, DList p, int data);

// -> fonction supprimerAvant(val L:liste d'objets, val p : liste d'objets): liste d'objet;
extern DList asde_dlist_delete_before(DList L, DList p);

// -> fonction supprimerVide(val L:liste d'objets): vide;
extern void asde_dlist_free(DList L);

#endif /* ASDE_DLIST_H */ 
