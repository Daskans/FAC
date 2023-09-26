#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "folt.h"

/*
* The update_next_colors function is called after the first position of the next_colors
* array (of the game_t whose reference is provided) is used. It moves the other colors
* one position to the beginning and add a new random color to the end of next_colors.
* To obtain a random number, you can use the get_random_integer function, whose 
* prototype is uint get_random_integer(uint start, uint stop);
* It returns a random unsigned integer greater of equal to start and lesser than or 
* equal to stop.

*/
void update_next_colors(game_t *p_game) {
    if (p_game==NULL) exit(EXIT_FAILURE);
    for (int i=0; i<NB_MAX_NEXT_COLORS-1; i++) {
        p_game->next_colors[i]=p_game->next_colors[i+1];
    }
    p_game->next_colors[NB_MAX_NEXT_COLORS]=get_random_integer(0, NB_MAX_COLORS);
}
/*
* The is_winning function determines if a game (referenced by p_game) ended 
* on a victory or not. It is typically used in the draw_awards function to adapt
* the ending message.
*/
bool is_winning(game_t *p_game);
/*
* The apply_move function updates the current state of the game (referenced by p_game) 
* by applying the movement in the direction referenced by p_next_direction. 
* The function assumes that the next direction is valid (it has already been checked).
*/
void apply_move(game_t *p_game);
/*
* The can_move function determines if, from the current state of the game (referenced
* by p_game), it is possible to apply a movement in any direction. It is typically 
* used to determine if we reached the end of the game.
* Notice that UP, DOWN, LEFT, and RIGHT are constants of type direction_t *
*/
bool can_move(game_t *p_game);
/*
* The end_of_program function determines if a game should be stopped considering its
* current state.
*/
bool end_of_program(game_t *p_game);

int main(void){
    position_t p;
    map_t m;
    game_t g; 
    /*init_game(&(g),&(m),&(p),"carte.xml");
    update_display(NULL,&(g));
	while( ! end_of_program(&(g)) ){
	    g.p_next_direction=read_direction(NULL);
		update_game(&(g));
		update_display(NULL,&(g));
	}
	draw_awards(NULL,&(g));
	delete_display(NULL);*/
	return EXIT_SUCCESS;
}