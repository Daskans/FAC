#include <stdio.h>
#include <stdlib.h>
#include "asde_dlist.h"
#include "asde_dlist_utilitary_functions.h"

int main(void){
    int n = 5;
    DList L = asde_dlist_create_empty();
    
    printf(" resultat de asde_dlist_prepend(L, i), i=0,1,2,3,4: \n");
    for(int i=0; i<n; i++){
        L = asde_dlist_prepend(L, i);
    }
    asde_dlist_print_intList(L);
    printf("\n");
    
    printf(" resultat de asde_dlist_delete_after(L, L) \n");
    L = asde_dlist_delete_after(L, L);
    asde_dlist_print_intList(L);
    printf("\n");
    
    printf(" resultat de asde_dlist_insert_after(L, L, 1000) \n");
    L = asde_dlist_insert_after(L, L, 1000);
    asde_dlist_print_intList(L);
    printf("\n");
    
    printf(" resultat de asde_dlist_delete_first(L)\n");
    L = asde_dlist_delete_first(L);
    asde_dlist_print_intList(L);
    printf("\n");
    
    printf(" resultat de asde_dlist_insert_before(L, L, 2000) \n");
    L = asde_dlist_insert_before(L, L, 2000);
    asde_dlist_print_intList(L);
    printf("\n");
    
    printf(" resultat de asde_dlist_delete_before(L, L) \n");
    L = asde_dlist_delete_before(L, L);
    asde_dlist_print_intList(L);
    printf("\n");
    
    printf(" resultat de asde_dlist_delete_before(L, L->next) \n");
    L = asde_dlist_delete_before(L, asde_dlist_next(L));
    asde_dlist_print_intList(L);
    printf("\n");

    L = asde_dlist_delete_list(L);

    return EXIT_SUCCESS;
}
