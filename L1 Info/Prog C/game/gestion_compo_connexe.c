#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "folt.h"

/*
* The compute_connected_component function computes the connected component of cells
* of the same color as the current position (referenced by p_pos), and returns the 
* size (i.e. the number of cells) of the connected component.
* The connected component is represented in a field of the map referenced by p_map,
* and is a boolean array of the same size as the cells array. For each cell, true
* means it belongs to the connected component.
* There is no need to consider min_nb_cells_in_cc in this function, that is tested
* later.
*/
uint compute_connected_component(map_t *p_map, position_t *p_pos);
/*
* The erase_connected_component function replace any cell of the connected component
* by an empty cell, and clean up the connected component list of the map referenced
* by p_map.
*/
void erase_connected_component(map_t *p_map);

int main(void){
    position_t p;
    map_t m;
    game_t g; 
    init_game(&(g),&(m),&(p),"carte.xml");
    update_display(NULL,&(g));
	while( ! end_of_program(&(g)) ){
	    g.p_next_direction=read_direction(NULL);
		update_game(&(g));
		update_display(NULL,&(g));
	}
	draw_awards(NULL,&(g));
	delete_display(NULL);
	return EXIT_SUCCESS;
}