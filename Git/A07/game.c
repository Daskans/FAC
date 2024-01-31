#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_struct.h"

game game_new(constraint* constraints, color* colors)
{
    if (constraints == NULL) {
        free(constraints);
        free(colors);
        exit(EXIT_FAILURE);
    }
    // We use game_new_empty_ext to create an empty game
    game game = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, FULL);
    for (uint length = 0; length < game->length; length++) {
        for (uint width = 0; width < game->width; width++) {  // Then we add the parameters to fill the game
            game->constraints[length * game->width + width] = constraints[length * game->width + width];
            if (colors == NULL) {
                game->colors[length * game->width + width] = EMPTY;
            } else {
                game->colors[length * game->width + width] = colors[length * game->width + width];
            }
        }
    }
    return game;
}

// We allocate space for the game struct, then set all the parameters to default
game game_new_empty(void)
{
    game game = malloc(sizeof(struct game_s));
    if (game == NULL) {
        fprintf(stderr, "game not created, error\n");
        exit(EXIT_FAILURE);
    }
    game->length = DEFAULT_SIZE;
    game->width = DEFAULT_SIZE;
    game->constraints = malloc(sizeof(constraint) * game->length * game->width);
    if (game->constraints == NULL) {
        fprintf(stderr, "game constraints not created, error\n");
        game_delete(game);
        exit(EXIT_FAILURE);
    }
    for (uint length = 0; length < game->length; length++) {
        for (uint width = 0; width < game->width; width++) {
            game->constraints[length * game->width + width] = UNCONSTRAINED;
        }
    }
    game->colors = malloc(sizeof(color) * game->length * game->width);
    if (game->colors == NULL) {
        fprintf(stderr, "game colors not created, error\n");
        game_delete(game);
        exit(EXIT_FAILURE);
    }
    for (uint length = 0; length < game->length; length++) {
        for (uint width = 0; width < game->width; width++) {
            game->colors[length * game->width + width] = EMPTY;
        }
    }
    game->wrapping = false;
    game->neighborhood = FULL;
    game->undo_stack = queue_new();
    game->redo_stack = queue_new();
    return game;
}

// We create a new game with the parameters of the game we want to copy, then copy the arrays.
game game_copy(cgame g)
{
    if (g == NULL || g->neighborhood < FULL || g->neighborhood > ORTHO_EXCLUDE) {
        exit(EXIT_FAILURE);
    }
    game game_copy = game_new_empty_ext(g->length, g->width, g->wrapping, g->neighborhood);
    if (game_copy == NULL || game_copy->length != g->length || game_copy->width != g->width ||
        game_copy->wrapping != g->wrapping || game_copy->neighborhood != g->neighborhood) {
        game_delete(game_copy);
        exit(EXIT_FAILURE);
    }
    for (uint length = 0; length < game_copy->length; length++) {
        for (uint width = 0; width < game_copy->width; width++) {
            if (game_get_constraint(g, length, width) < -1 || game_get_constraint(g, length, width) > 9 ||
                game_get_color(g, length, width) < EMPTY || game_get_color(g, length, width) > BLACK) {
                game_delete(game_copy);
                exit(EXIT_FAILURE);
            }
            game_set_constraint(game_copy, length, width, game_get_constraint(g, length, width));
            game_set_color(game_copy, length, width, game_get_color(g, length, width));
            if (game_get_color(game_copy, length, width) != game_get_color(g, length, width) ||
                game_get_constraint(game_copy, length, width) != game_get_constraint(g, length, width)) {
                game_delete(game_copy);
                exit(EXIT_FAILURE);
            }
        }
    }
    for (uint length = 0; length < game_copy->length; length++) {
        for (uint width = 0; width < game_copy->width; width++) {  // We check that both games come with the same status
            if (game_get_status(game_copy, length, width) != game_get_status(g, length, width)) {
                game_delete(game_copy);
                exit(EXIT_FAILURE);
            }
        }
    }
    return game_copy;
}

// We just check that each part of g1 is the same for g2
bool game_equal(cgame g1, cgame g2)
{
    if (g1 == NULL || g2 == NULL) {
        exit(EXIT_FAILURE);
    }
    if (g1->length != g2->length || g1->width != g2->width) {
        return false;
    }
    if (g1->neighborhood != g2->neighborhood) {
        return false;
    }
    if (g1->wrapping != g2->wrapping) {
        return false;
    }
    for (int length = 0; length < g1->length; length++) {
        for (int width = 0; width < g1->width; width++) {
            if (game_get_color(g1, length, width) != game_get_color(g2, length, width)) {
                return false;
            }
            if (game_get_constraint(g1, length, width) != game_get_constraint(g2, length, width)) {
                return false;
            }
            if (game_get_status(g1, length, width) != game_get_status(g2, length, width)) {
                return false;
            }
        }
    }
    return true;
}

// Make sure that we don't forget to free arrays before freeing the structure
void game_delete(game g)
{
    if (g != NULL) {
        if (g->constraints != NULL) {
            free(g->constraints);
        }
        if (g->colors != NULL) {
            free(g->colors);
        }
        if (g->redo_stack != NULL) {
            queue_free_full(g->redo_stack, free);
        }
        if (g->undo_stack != NULL) {
            queue_free_full(g->undo_stack, free);
        }
        free(g);
    }
}

void game_set_constraint(game g, uint i, uint j, constraint n)
{
    if (g == NULL || i >= g->length || j >= g->width || n < -1 || n > 9) {
        game_delete(g);
        exit(EXIT_FAILURE);
    }
    g->constraints[i * g->width + j] = n;
}

void game_set_color(game g, uint i, uint j, color c)
{
    if (g == NULL) {
        fprintf(stderr, "no game to set color on\n");
        game_delete(g);
        exit(EXIT_FAILURE);
    }
    if (i >= g->length || j >= g->width) {
        fprintf(stderr, "error in coordonates\n");
        game_delete(g);
        exit(EXIT_FAILURE);
    }
    if (c < EMPTY || c > BLACK) {
        fprintf(stderr, "not a color\n");
        game_delete(g);
        exit(EXIT_FAILURE);
    }
    g->colors[(i * g->width) + j] = c;
}

constraint game_get_constraint(cgame g, uint i, uint j)
{
    if (g == NULL || i >= g->length || j >= g->width) {
        exit(EXIT_FAILURE);
    }
    return g->constraints[i * g->width + j];
}

color game_get_color(cgame g, uint i, uint j)
{
    if (g == NULL || i >= g->length || j >= g->width) {
        exit(EXIT_FAILURE);
    }
    return g->colors[i * g->width + j];
}

// Auxiliary function to lighten game_get_next_square :
void change_coordinates(cgame g, uint* pi_next, uint* pj_next, int nxt_square_index_i, int nxt_square_index_j,
                        bool* test)
{
    if (nxt_square_index_i >= 0) {
        *pi_next = nxt_square_index_i;
    }
    if (nxt_square_index_j >= 0) {
        *pj_next = nxt_square_index_j;
    }
    // If no wrapping, we just have to check if the indexes of the "next_square", according to the direction, are in
    // bounds
    if (g->wrapping != true) {
        if (nxt_square_index_i == g->length || nxt_square_index_j == g->width || nxt_square_index_i < 0 ||
            nxt_square_index_j < 0) {
            *test = false;
        } else {
            *test = true;
        }
    }
    // Otherwise, if nxt_square_index_i or nxt_square_index_j are out of bonds, then we change pi_next or pj_next
    // accordingly
    else {
        *test = true;
        if (nxt_square_index_i == g->length) {
            *pi_next = 0;
        } else if (nxt_square_index_i < 0) {
            *pi_next = g->length - 1;
        }
        if (nxt_square_index_j == g->width) {
            *pj_next = 0;
        } else if (nxt_square_index_j < 0) {
            *pj_next = g->width - 1;
        }
    }
}

// We apply the previous function to different indexes depending on the direction we pass in parameter of
// game_get_next_square.
bool game_get_next_square(cgame g, uint i, uint j, direction dir, uint* pi_next, uint* pj_next)
{
    if (g == NULL || i >= g->length || j >= g->width || pi_next == NULL || pj_next == NULL || dir < HERE ||
        dir > DOWN_RIGHT) {
        free(pi_next);
        free(pj_next);
        exit(EXIT_FAILURE);
    }
    int nxt_square_index_i = i;
    int nxt_square_index_j = j;
    bool test;
    if (dir == HERE) {
        change_coordinates(g, pi_next, pj_next, nxt_square_index_i, nxt_square_index_j, &test);
    } else if (dir == LEFT) {
        change_coordinates(g, pi_next, pj_next, nxt_square_index_i, nxt_square_index_j - 1, &test);
    } else if (dir == RIGHT) {
        change_coordinates(g, pi_next, pj_next, nxt_square_index_i, nxt_square_index_j + 1, &test);
    } else if (dir == UP) {
        change_coordinates(g, pi_next, pj_next, nxt_square_index_i - 1, nxt_square_index_j, &test);
    } else if (dir == DOWN) {
        change_coordinates(g, pi_next, pj_next, nxt_square_index_i + 1, nxt_square_index_j, &test);
    } else if (dir == UP_RIGHT) {
        change_coordinates(g, pi_next, pj_next, nxt_square_index_i - 1, nxt_square_index_j + 1, &test);
    } else if (dir == DOWN_RIGHT) {
        change_coordinates(g, pi_next, pj_next, nxt_square_index_i + 1, nxt_square_index_j + 1, &test);
    } else if (dir == UP_LEFT) {
        change_coordinates(g, pi_next, pj_next, nxt_square_index_i - 1, nxt_square_index_j - 1, &test);
    } else if (dir == DOWN_LEFT) {
        change_coordinates(g, pi_next, pj_next, nxt_square_index_i + 1, nxt_square_index_j - 1, &test);
    }
    if (test == false) {
        *pi_next = i;
        *pj_next = j;
    }
    return test;
}

// We look at the constraint of the tile then act differently whether it's -1 or not
status game_get_status(cgame g, uint i, uint j)
{
    if (g == NULL || i >= g->length || j >= g->width) {
        exit(EXIT_FAILURE);
    }
    status status;
    constraint constraint = game_get_constraint(g, i, j);
    // If it's not -1, we count all the neighbors that are black, then those that are white, and we check what status is
    // correct
    if (constraint != -1) {
        uint compute_color_black = game_nb_neighbors(g, i, j, BLACK);
        uint compute_color_white = game_nb_neighbors(g, i, j, WHITE);
        int total = compute_color_black + compute_color_white + game_nb_neighbors(g, i, j, EMPTY);
        if (constraint == compute_color_black && total - constraint == compute_color_white &&
            total - compute_color_black - compute_color_white == 0) {
            status = SATISFIED;
        } else if (compute_color_black > constraint || compute_color_white > total - constraint) {
            status = ERROR;
        } else {
            status = UNSATISFIED;
        }
    }
    // Otherwise, we just check if the tile has any empty neighbor to decide the status
    else {
        uint compute_color_empty = game_nb_neighbors(g, i, j, EMPTY);
        if (compute_color_empty == 0) {
            status = SATISFIED;
        } else {
            status = UNSATISFIED;
        }
    }
    if (status != ERROR && status != UNSATISFIED && status != SATISFIED) {
        exit(EXIT_FAILURE);
    }
    return status;
}

// Auxiliary function to lighten game_nb_neighbors
int count_neighbors(cgame g, uint i, uint j, direction mini, direction maxi, color c)
{
    int count = 0;
    // We browse the directions of the game's neighborhood
    for (direction dir = mini; dir <= maxi; dir++) {
        uint index_length;
        uint index_width;
        // If it's a valid tile, we check if the color of this tile is the same as the one we seek. If yes, we add one
        // to the count
        if (game_get_next_square(g, i, j, dir, &index_length, &index_width) == true) {
            if (game_get_color(g, index_length, index_width) == c) {
                count += 1;
            }
        }
    }
    return count;
}

// We apply the previous function to different directions depending on the game's neighborhood
int game_nb_neighbors(cgame g, uint i, uint j, color c)
{
    if (g == NULL || i >= g->length || j >= g->width || c < EMPTY || c > BLACK) {
        exit(EXIT_FAILURE);
    }
    int neighbors_count = 0;
    if (g->neighborhood == FULL) {
        neighbors_count = count_neighbors(g, i, j, HERE, DOWN_RIGHT, c);
    } else if (g->neighborhood == ORTHO) {
        neighbors_count = count_neighbors(g, i, j, HERE, RIGHT, c);
    } else if (g->neighborhood == FULL_EXCLUDE) {
        neighbors_count = count_neighbors(g, i, j, UP, DOWN_RIGHT, c);
    } else if (g->neighborhood == ORTHO_EXCLUDE) {
        neighbors_count = count_neighbors(g, i, j, UP, RIGHT, c);
    }
    return neighbors_count;
}

// When we play a move, we clean the redo_stack, then we initialize a move struct that we fill, to finally change the
// color of the tile and add the move to the undo_stack
void game_play_move(game g, uint i, uint j, color c)
{
    if (g == NULL || g->colors == NULL || g->constraints == NULL || i >= g->length || j >= g->width) {
        game_delete(g);
        exit(EXIT_FAILURE);
    }
    if (c < EMPTY || c > BLACK) {
        exit(EXIT_FAILURE);
    }
    if (!queue_is_empty(g->redo_stack)) {
        queue_clear(g->redo_stack);
    }
    move move = malloc(sizeof(struct move_s));
    if (move == NULL) {
        exit(EXIT_FAILURE);
    }
    move->x = i;
    move->y = j;
    move->move_previous = game_get_color(g, i, j);
    move->move_color = c;
    // When we play a move, we have to add the state of the tile to the undo stack before playing the move. Thanks to
    // that, when we undo we can get the last tile back to the color it was.
    g->colors[i * g->width + j] = c;
    queue_push_head(g->undo_stack, move);
}

// We just check if all tiles' status are satisfied and if no tiles are left empty
bool game_won(cgame g)
{
    if (g == NULL || g->colors == NULL || g->constraints == NULL) {
        exit(EXIT_FAILURE);
    }
    bool won = true;
    for (uint i = 0; i < g->length; i++) {
        for (uint j = 0; j < g->width; j++) {
            if (game_get_color(g, i, j) == EMPTY || game_get_status(g, i, j) == UNSATISFIED ||
                game_get_status(g, i, j) == ERROR) {
                won = false;
            }
        }
    }
    return won;
}

// We set all tiles' color to empty and clear the undo and redo stacks (by freeing each move in the stacks)
void game_restart(game g)
{
    if (g == NULL || g->colors == NULL || g->constraints == NULL) {
        game_delete(g);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < g->length; i++) {
        for (int j = 0; j < g->width; j++) {
            game_set_color(g, i, j, EMPTY);
        }
    }
    queue_clear_full(g->undo_stack, free);
    queue_clear_full(g->redo_stack, free);
}