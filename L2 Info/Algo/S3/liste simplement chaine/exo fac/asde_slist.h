/*
* This file is a copy of the orginal.
* Modification will not be taken into account.
*/

#ifndef ASDE_SLIST_H
#define ASDE_SLIST_H

#include <stdbool.h>

typedef struct SCell SCell;
typedef SCell * SList;

// returns an empty list
extern SList asde_slist_create_empty(void);

// tests whether a SList is empty
extern  bool asde_slist_isEmpty(SList L);

//adds a new element on the start of the list -> fonction insereEnTete(val L: liste d'objets, val x objet): liste d'objets;
extern SList asde_slist_prepend(SList L, int data);

// -> fonction supprimerEnTete(val L: liste d'objet): liste d'objet;
extern SList asde_slist_delete_first(SList L);

// -> fonction insererApres(val L:liste d'objet, val p : liste d'objets, val x: objet): liste d'objet;
extern SList asde_slist_insert_after(SList L, SList p, int data);

// -> fonction supprimerApres(val L:liste d'objet, val p : liste d'objets): liste d'objet;
extern SList asde_slist_delete_after(SList L, SList p);

// gets next element in a SList ->  fonction suivant(val p:liste): liste; 
extern  SList  asde_slist_next(SList p);

// gets data in a SList ->  fonction valeur(val p:liste): objet;
extern  int asde_slist_data(SList p);

// frees an already empty SList
extern void asde_slist_free(SList L);

#endif /* ASDE_SLIST_H */ 
