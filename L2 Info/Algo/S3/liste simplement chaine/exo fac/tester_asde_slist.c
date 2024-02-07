#include <stdio.h>
#include <stdlib.h>
#include "asde_slist.h"
#include "asde_slist_utilitary_functions.h"

int main(void){
    int n = 5;
    SList L = asde_slist_create_empty();
    
    printf(" resultat de  asde_slist_prepend(L, i), i=0,1,2,3,4: \n");
    for(int i=0; i< n; i++){
        L = asde_slist_prepend(L, i);
    }
    asde_slist_print_intList(L);
    printf("\n");
    
    printf(" resultat de  asde_slist_delete_after(L, L) \n");
    L = asde_slist_delete_after(L, L);
    asde_slist_print_intList(L);
    printf("\n");
    
    printf(" resultat de  asde_slist_insert_after(L, L, 1000) \n");
    L = asde_slist_insert_after(L, L, 1000);
    asde_slist_print_intList(L);
    printf("\n");
    
    printf(" resultat de  asde_slist_delete_first(L)\n");
    L = asde_slist_delete_first(L);
    asde_slist_print_intList(L);
    printf("\n");
    
    L = asde_slist_delete_list(L);
    
    return EXIT_SUCCESS;
}