#include <stdio.h>
#include <stdlib.h>
#include "asde_dlist.h"

struct DCell{
    int data;
    struct DCell* next;
    struct DCell* previous;
};

static void memoryError(void){
    fprintf(stderr, "Not enough memory!\n");
    exit(EXIT_FAILURE);
}

static DList asde_dlist_alloc(void){
    DList p = malloc(sizeof(struct DCell));
    if (!p)
        memoryError();
    p->next = NULL;
    p->previous = NULL;
    return p;
}

void asde_dlist_free (DList L){
    free(L);
    L = NULL;
}

DList asde_dlist_create_empty(void){
    return NULL;
}

bool asde_dlist_isEmpty (DList L){
    return (!L);
}

DList asde_dlist_next(DList L) {
    if (!L) {
        fprintf(stderr, "No list given\n");
        exit(EXIT_FAILURE);
    }
    return L->next;
}

DList asde_dlist_prev (DList L){
    if (!L) {
        fprintf(stderr, "No list given\n");
        exit(EXIT_FAILURE);
    }
    return L->previous;
}

int asde_dlist_data (DList L){
    if (!L) {
        fprintf(stderr, "No list given\n");
        exit(EXIT_FAILURE);
    }
    return L->data;
}

DList asde_dlist_prepend (DList L, int data){
    DList newValue = asde_dlist_alloc();
    newValue->data = data;
    newValue->next = L;
    if (L != NULL) {
        L->previous = newValue;
    }
    return newValue;
}

DList asde_dlist_delete_first (DList L){
    if (!L) {
        fprintf(stderr, "No list given\n");
        exit(EXIT_FAILURE);
    }
    DList headNext = L->next;
    if (headNext) {
        headNext->previous = NULL;
    }
    asde_dlist_free(L);
    return headNext;
}

DList asde_dlist_insert_after(DList L, DList p, int data){
    if (!p) {
        fprintf(stderr, "No list given\n");
        exit(EXIT_FAILURE);
    }
    DList newValue = asde_dlist_alloc();
    newValue->data = data;
    newValue->next = p->next;
    newValue->previous = p;
    if (!(p->next)) {
        p->next->previous = newValue;
    }
    p->next = newValue;
    return newValue;
}

DList asde_dlist_delete_after (DList L, DList p){
    if (!p || !(p->next)) {
        fprintf(stderr, "No list given\n");
        exit(EXIT_FAILURE);
    }
    DList nodeToDelete = p->next;
    p->next = nodeToDelete->next;
    if (nodeToDelete->next != NULL) {
        nodeToDelete->next->previous = p;
    }
    asde_dlist_free(nodeToDelete);
    return L;
}

DList asde_dlist_insert_before(DList L, DList p, int data) {
    if (!p) {
        fprintf(stderr, "No list given\n");
        exit(EXIT_FAILURE);
    }
    DList newValue = asde_dlist_alloc();
    newValue->data = data;
    newValue->next = p;
    newValue->previous = p->previous;
    if (p->previous != NULL) {
        p->previous->next = newValue;
    }
    p->previous = newValue;
    if (L == p) {
        return newValue;
    }
    return L;
}
DList asde_dlist_delete_before (DList L, DList p){
    if (!p || !(p->previous)) {
        fprintf(stderr, "No list given\n");
        exit(EXIT_FAILURE);
    }
    DList nodeToDelete = p->previous;
    if (L == nodeToDelete) {
        L = p;
    }
    p->previous = nodeToDelete->previous;
    if (nodeToDelete->previous != NULL) {
        nodeToDelete->previous->next = p;
    }
    asde_dlist_free(nodeToDelete);
    return L;
}
