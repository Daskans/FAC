#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "folt.h"

/*
* The is_border_cell function determines if a given position index corresponds to a
* position of a border cell according to the properties of the map (mainly its dimensions). 
* NOTICE: this function is called by the initiate_map_cells function in order to 
* determine if a given cell should be initiate to BORDER_CELL or EMPTY_CELL value.
*/
bool is_border_cell(map_t *p_map, uint pos_index) {
    if (p_map==NULL) exit(EXIT_FAILURE);
    if (pos_index>=NB_MAX_CELLS) exit(EXIT_FAILURE);
    uint nbc = p_map->nb_columns+2;
    uint nbl = p_map->nb_lines+2;
    int current_slice = pos_index/nbc;
    if (current_slice == 0 || 
        current_slice == nbl-1 || 
        pos_index%nbc == 0 ||
        pos_index == ((current_slice+1)*nbc)-1 ||
        pos_index > nbc*nbl) {
        return true;
    } 
    return false;
}
/*
* The is_position_valid function determines if a given position (referenced by
* p_position) can be part of a cells array. Notice this test is NOT about a particular
* map, but rather to see if a position (x,y) could belong to a valid map given the
* limitation in number of cells NB_MAX_CELLS.
*/
bool is_position_valid(position_t *p_position) {
    if (p_position==NULL) exit(EXIT_FAILURE);
    uint x = p_position->x+1;
    uint y = p_position->y+1;
    if (x*y<=NB_MAX_CELLS) return true;
    return false;
}
/*
* The is_position_valid_and_visible function determines if a given position (referenced
* by p_position) belongs to the visible part of the map.
*/
bool is_position_valid_and_visible(map_t *p_map, position_t *p_position) {
    if (p_map==NULL || p_position==NULL) exit(EXIT_FAILURE);
    uint nbc = p_map->nb_columns;
    uint nbl = p_map->nb_lines;
    uint x = p_position->x;
    uint y = p_position->y;
    if (is_position_valid(p_position)) {
        if (x<=nbc && y<=nbl && x>0 && y>0) return true;
        return false;
    }
    return false;
}
/*
* The valid_position_to_index function transforms a given position, referenced by p_position
* (supposed to be valid if the pointer is valid) into the corresponding index in the cells 
* field of the map referenced by p_map.
* In the case of an invalid position, the result of the function is unpredictable.
*/
uint valid_position_to_index(map_t *p_map, position_t *p_position) {
    if (p_map==NULL || p_position==NULL) exit(EXIT_FAILURE);
    uint nbc = p_map->nb_columns+2;
    uint x = p_position->x;
    uint y = p_position->y;
    uint index=x+y*nbc;
    return index;
}
/*
* The valid_index_to_position function transforms a given index i (supposed to be valid),
* which corresponds to an index in the array of cells of the map referenced by p_map,
* into a position_t and stores it into the variable referenced by p_position.
* In case of an invalid index, the result of the function is unpredictable.
*/
void valid_index_to_position(map_t *p_map, uint i, position_t *p_position) {
    if (p_map==NULL || p_position==NULL) exit(EXIT_FAILURE);
    uint nbc = p_map->nb_columns+2;
    p_position->x = i%nbc;
    p_position->y = i/nbc;
}
/*
* The get_cell function returns the color_t of the cell of the map
* (referenced by p_map) in the position referenced by p_position.
* In the case of an invalid position, the function quits the program
* with an error message. 
* This function can be applied to both invisible and visible
* cells of the map.
*/
color_t get_cell(map_t *p_map, position_t *p_position) {
    if (p_map==NULL || p_position==NULL || is_position_valid(p_position) == false) exit(-1);
    return p_map->cells[valid_position_to_index(p_map, p_position)];
}
/*
* The set_color_cell function modifies the color_t of a visible cell at the position 
* referenced by p_position. 
* In the case of an invalid position or invalid color_id, the function quits
* the program with an error message.
*/
void set_color_cell(map_t *p_map, position_t *p_position, color_t color_id) {
    if (p_map==NULL || 
        p_position==NULL || 
        color_id>p_map->nb_colors|| 
        is_position_valid_and_visible(p_map, p_position) == false) exit(EXIT_FAILURE);
    p_map->cells[valid_position_to_index(p_map, p_position)]=color_id;
    
}
/*
* The set_empty_cell function removes any color_t of the visible cell at the given 
* position, referenced by p_position. 
* In the case of an invalid position, the function quits the program with 
* an error message.
*/
void set_empty_cell(map_t *p_map, position_t *p_position) {
    if (p_map==NULL || 
        p_position==NULL || 
        is_position_valid_and_visible(p_map, p_position) == false) exit(EXIT_FAILURE);
    p_map->cells[valid_position_to_index(p_map, p_position)]=EMPTY_CELL;
}
/*
* The movement_is_allowed function determines if, in the map referenced by p_map, 
* starting from the position referenced by p_position, adding a color in the direction
* referenced by p_direction is possible. 
* In the case of at least one invalid arguement, the function 
* quits the program with an error message.
*/
bool movement_is_allowed(map_t *p_map, position_t *p_position, direction_t *p_direction ) {
    if (p_map==NULL || p_position==NULL) exit(EXIT_FAILURE);
    position_t *new_pos;
    new_pos->x = p_position->x + p_direction->deltax;
    new_pos->y = p_position->y + p_direction->deltay;
    //translate(p_position, p_direction, new_pos); 
    if (is_border_cell(p_map, valid_position_to_index(p_map, new_pos))==true) return false;
    return true;
}

int main(void){
    position_t p;
    map_t m;
    game_t g; 
    /*init_game(&(g),&(m),&(p),"carte.xml");
    update_ascii_display(&(g));
	while( ! end_of_program(&(g)) ){
	    g.p_next_direction=read_direction(NULL);
		update_game(&(g));
		update_display(NULL,&(g));
	}
	draw_ascii_awards(&(g));
	delete_display(NULL);*/
	return EXIT_SUCCESS;
}