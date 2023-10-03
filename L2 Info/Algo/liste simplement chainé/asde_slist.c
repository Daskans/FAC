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
    // TO DO
}

SList asde_slist_next(SList p){
    // TO DO
}

int asde_slist_data(SList p){
    // TO DO
}

SList asde_slist_prepend(SList L, int data){
    // TO DO
}

SList asde_slist_delete_first(SList L){
    // TO DO
}

SList asde_slist_insert_after(SList L, SList p, int data){
    // TO DO
}

SList asde_slist_delete_after(SList L, SList p){
    // TO DO
}
