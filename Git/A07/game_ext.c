#include "game_ext.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_struct.h"
#include "queue.h"

// Same idea as game_new, but with more arguments
game game_new_ext(uint nb_rows, uint nb_cols, constraint* constraints, color* colors, bool wrapping,
                  neighbourhood neigh)
{
    if (constraints == NULL) {
        free(constraints);
        free(colors);
        exit(EXIT_FAILURE);
    }
    game g = game_new_empty_ext(nb_rows, nb_cols, wrapping, neigh);
    for (uint row_number = 0; row_number < g->length; row_number++) {
        for (uint column_number = 0; column_number < g->width; column_number++) {
            g->constraints[row_number * g->width + column_number] = constraints[row_number * g->width + column_number];
            if (colors == NULL) {
                g->colors[row_number * g->width + column_number] = EMPTY;
            } else {
                g->colors[row_number * g->width + column_number] = colors[row_number * g->width + column_number];
            }
        }
    }
    return g;
}

// Same idea as game_new_empty, but with more arguments
game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping, neighbourhood neigh)
{
    game g = malloc(sizeof(struct game_s));
    if (g == NULL) {
        fprintf(stderr, "game not created, error\n");
        exit(EXIT_FAILURE);
    }
    g->length = nb_rows;
    g->width = nb_cols;
    g->wrapping = wrapping;
    g->neighborhood = neigh;
    g->constraints = malloc(sizeof(constraint) * g->length * g->width);
    if (g->constraints == NULL) {
        fprintf(stderr, "game constraints not created, error\n");
        game_delete(g);
        exit(EXIT_FAILURE);
    }
    for (uint row_number = 0; row_number < g->length; row_number++) {
        for (uint column_number = 0; column_number < g->width; column_number++) {
            g->constraints[row_number * g->width + column_number] = UNCONSTRAINED;
        }
    }
    g->colors = malloc(sizeof(color) * g->length * g->width);
    if (g->colors == NULL) {
        fprintf(stderr, "game colors not created, error\n");
        game_delete(g);
        exit(EXIT_FAILURE);
    }
    for (uint row_number = 0; row_number < g->length; row_number++) {
        for (uint column_number = 0; column_number < g->width; column_number++) {
            g->colors[row_number * g->width + column_number] = EMPTY;
        }
    }
    g->undo_stack = queue_new();
    g->redo_stack = queue_new();
    return g;
}

uint game_nb_rows(cgame g)
{
    if (g == NULL) {
        exit(EXIT_FAILURE);
    }
    return g->length;
}

uint game_nb_cols(cgame g)
{
    if (g == NULL) {
        exit(EXIT_FAILURE);
    }
    return g->width;
}

bool game_is_wrapping(cgame g)
{
    if (g == NULL) {
        exit(EXIT_FAILURE);
    }
    return g->wrapping;
}

neighbourhood game_get_neighbourhood(cgame g)
{
    if (g == NULL) {
        exit(EXIT_FAILURE);
    }
    return g->neighborhood;
}

// If undo_stack isn't empty, we remove the move on top of the stack, then we bring back this move's tile to it's former
// state, and add this move to the redo_stack
void game_undo(game g)
{
    if (g == NULL) {
        exit(EXIT_FAILURE);
    }
    if (queue_is_empty(g->undo_stack)) {
        return;
    }
    if (!queue_is_empty(g->undo_stack)) {
        move move = queue_pop_head(g->undo_stack);
        // if g->undo_stack contain information pre_move, like (x , y, EMPTY) before the move (x, y, BLACK)
        if (move == NULL) {
            exit(EXIT_FAILURE);
        }
        game_set_color(g, move->x, move->y, move->move_previous);
        queue_push_head(g->redo_stack, move);
    }
}

// If redo_stack isn't empty, we remove the move on top of the stack, then bring back the move's tile before the last
// undo, and add this move to the undo_stack
void game_redo(game g)
{
    if (g == NULL) {
        exit(EXIT_FAILURE);
    }
    if (queue_is_empty(g->redo_stack)) {
        return;
    }
    move move = queue_pop_head(g->redo_stack);
    if (move == NULL) {
        exit(EXIT_FAILURE);
    }
    game_set_color(g, move->x, move->y, move->move_color);
    queue_push_head(g->undo_stack, move);
}
