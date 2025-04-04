#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "folt.h"

/*
* Given a potential color_t c, the function returns a character corresponding to 
* the color code if this last is a valid color (less than 10); if not, it should 
* print out an error message and quit the program.
* Examples : 
*   + get_ascii_color(6) should return '6'
*   + get_ascii_color(3) should return '3'
*   + get_ascii_color(-1) should print out an error and quit the program
*   + get_ascii_color(10) should print out an error and quit the program
*/
char get_ascii_color(color_t c) {
    if (c > 10 || c < 0) {
        printf("error : invalide color");
        exit(EXIT_FAILURE);
    }
    return c;
}
/*
* The function prints a message depending on the state of the game. If the user
* won the game (its score is greater than the goal score), it prints out "YOU WIN !".
* If not, it prints out "GAME OVER !".
* Instead of comparing the current score to the goal score, 
* here you are asked to use the is_winning function. Its prototype is: 
* bool is_winning(game_t *p_game);
*/
void draw_ascii_awards(game_t *p_game) {
    if (p_game==NULL) exit(EXIT_FAILURE);
    if (is_winning(p_game)) {
        printf("YOU WIN !");
    } else {
        printf("GAME OVER !");
    }
}
/*
* The function prints a message displaying the colors to come, the actual score 
* and the goal score. 
* Example: 
* Next colors : 2 3 1
* 3 / 30
* where 2, 3 and 1 are the next colors to come in appearing order (2 is the next, 
* 3 comes after it, and then 1),
* 3 is the current score, and 30 is the goal score.
*/
void draw_ascii_menu(game_t *p_game) {
    if (p_game==NULL) exit(EXIT_FAILURE);
    for (uint i=0; i<NB_MAX_NEXT_COLORS; i++) {
        printf("%d ",p_game->next_colors[i]);
    }
    printf("\n %d / %d",p_game->score, p_game->p_map->goal);
}
/*
* The function draw_ascii_tiles prints the game map.
* Each cell of the map is printed using three characters : a space, the color, and
* if the cell is the one corresponding to the position referenced by  p_actual_pos, 
* a '!' is added (otherwise a space is added).
* An empty cell is printed as a space followed by an 'X' and another space.
* Cells belonging to the border are not printed out.
* In the folowwing example, spaces are replaced by '_'
* Example:
*_X__X__X__X__X_
*_X__X__X__X__X_
*_X__2__3__1__2_
*_X__0__1__1__3_
*_X__1__X__2__0!
*_X__3__2__1__X_
*_X__X__X__X__X_
* To obtain the color of a cell, you can use the get_cell function. Its prototype is:
* color_t get_cell(map_t *p_map, position_t *p_position);
*/
void draw_ascii_tiles(map_t *p_map, position_t *p_actual_pos) {
    if (p_map==NULL||p_actual_pos==NULL) exit(EXIT_FAILURE);
    for (uint i=0; i<NB_MAX_CELLS; i++) {
        position_t x=
        if (!is_border_cell(p_map, p_map->cells[i])) {
            if(get_cell(p_map, )==EMPTY_CELL) {
                printf(" X ");
            } else {
                printf(" %d",get_cell(p_map, p_map->cells[i]));
                if (i==p_actual_pos) printf("!");
                else printf(" ");
            }
        }
        if (p_map->cells[i]%p_map->nb_columns==0) printf("\n");
    }
}

/*
* The update_ascii_display function only prints all the graphical elements of the game.
* That is the map and the menu (colors to come, the current score and the goal score).
* It should not imply duplicate code.
*/
void update_ascii_display(game_t *p_game) {
    if (p_game == NULL) exit(EXIT_FAILURE);
    draw_ascii_tiles(p_game->p_map, p_game->p_actual_position);
    draw_ascii_menu(p_game);
}

int main(void){
    position_t p;
    map_t m;
    game_t g; 
    /*//init_game(&(g),&(m),&(p),"carte.xml");
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