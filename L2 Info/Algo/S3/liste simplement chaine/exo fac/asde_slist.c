#include <stdio.h>
#include <stdlib.h>
#include "asde_slist.h"

struct SCell{
    int data;
    struct SCell *next;
};

static void memoryError(void){
    fprintf(stderr, "Not enough memory!\n");
    exit(EXIT_FAILURE);
}

static SList asde_slist_alloc(void){
    SList p = (SCell*)malloc(sizeof(SCell));
    if (p == NULL)
        memoryError();
    p->next = NULL;
    return p;
}

void asde_slist_free(SList L){
    free(L);
}

SList asde_slist_create_empty(void){
    return NULL;
}

bool asde_slist_isEmpty(SList L){
    return L == NULL;
}

SList asde_slist_next(SList p) {
    if (p == NULL) {
        return NULL;
    }
    return p->next;
}

int asde_slist_data(SList p) {
    if (p == NULL) {
        fprintf(stderr, "Error: Invalid pointer!\n");
        exit(EXIT_FAILURE);
    }
    return p->data;
}

SList asde_slist_prepend(SList L, int data){
    SList newNode = asde_slist_alloc();
    newNode->data = data;
    newNode->next = L;
    return newNode;
}

SList asde_slist_delete_first(SList L){
    if (L == NULL) {
        return NULL;
    }
    SList nextNode = L->next;
    asde_slist_free(L);
    return nextNode;
}

SList asde_slist_insert_after(SList L, SList p, int data){
    if (p == NULL) {
        fprintf(stderr, "Error: Invalid pointer!\n");
        exit(EXIT_FAILURE);
    }
    SList newNode = asde_slist_alloc();
    newNode->data = data;
    newNode->next = p->next;
    p->next = newNode;
    return L;
}

SList asde_slist_delete_after(SList L, SList p){
    if (p == NULL || p->next == NULL) {
        return L;
    }
    SList nextNode = p->next;
    p->next = nextNode->next;
    asde_slist_free(nextNode);
    return L;
}
