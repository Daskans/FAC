#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"

constraint CONS[DEFAULT_SIZE * DEFAULT_SIZE] = {0,  -1, -1, 3,  -1, -1, 5,  -1, -1, -1, -1, -1, 4,
                                                -1, 1,  6,  -1, 6,  3,  -1, -1, -1, -1, -1, -1};
color cs[DEFAULT_SIZE * DEFAULT_SIZE] = {EMPTY};

bool test_dummy() { return true; }

bool test_game_equal()
{
    game g1 = game_default();
    game g2 = game_default();
    game g3 = game_default_solution();
    game g4 = game_default_solution();
    bool t1 = (g1 != g2);
    bool t2 = true;
    bool t3 = true;
    bool t4 = true;
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0; j < DEFAULT_SIZE; j++) {
            if (game_get_color(g1, i, j) != game_get_color(g2, i, j) ||
                game_get_constraint(g1, i, j) != game_get_constraint(g2, i, j)) {
                t2 = false;
            }
            if (game_get_color(g3, i, j) != game_get_color(g4, i, j) ||
                game_get_constraint(g3, i, j) != game_get_constraint(g4, i, j)) {
                t3 = false;
            }
            if (game_get_color(g1, i, j) == game_get_color(g4, i, j)) {
                t4 = false;
            }
        }
    }
    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    game_delete(g4);
    if (t1 && t2 && t3 && t4) {
        return true;
    }
    return false;
}

bool test_game_get_constraint()
{
    game g = game_default();
    bool t1 = game_get_constraint(g, 0, 0) == -1;
    bool t2 = game_get_constraint(g, 0, 1) == -1;
    bool t3 = game_get_constraint(g, 0, 0) == 0;
    bool t4 = game_get_constraint(g, 0, 0) == 9;
    game_delete(g);
    if (!t1 && t2 && t3 && !t4) {
        return true;
    }
    return false;
}

bool test_game_get_color()
{
    game g = game_default();
    game g2 = game_default_solution();
    bool t1 = game_get_color(g, 0, 0) == EMPTY;
    bool t2 = game_get_color(g2, 0, 2) == BLACK;
    bool t3 = game_get_color(g2, 0, 0) == WHITE;
    bool t4 = game_get_color(g2, 0, 0) == EMPTY;
    game_delete(g);
    game_delete(g2);
    if (t1 && t2 && t3 && !t4) {
        return true;
    }
    return false;
}

bool test_game_nb_neighbors()
{
    game g1 = game_default();
    game g2 = game_default_solution();
    game g3 = game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, CONS, cs, true, FULL);
    game g4 = game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, CONS, cs, true, ORTHO);
    bool t1 = game_nb_neighbors(g1, 0, 0, EMPTY) == 4;
    bool t6 = game_nb_neighbors(g1, 0, 0, WHITE) == 4;
    bool t2 = game_nb_neighbors(g1, 0, 0, EMPTY) == 9;
    bool t7 = game_nb_neighbors(g3, 0, 0, EMPTY) == 9;
    bool t11 = game_nb_neighbors(g4, 0, 0, EMPTY) == 5;
    game_play_move(g1, 0, 0, WHITE);
    game_play_move(g3, 0, 0, BLACK);
    game_play_move(g4, 0, 0, BLACK);
    bool t3 = game_nb_neighbors(g1, 0, 0, WHITE) == 1;
    bool t4 = game_nb_neighbors(g2, 0, 0, WHITE) == 4;
    bool t5 = game_nb_neighbors(g2, 0, 0, BLACK) == 4;
    bool t8 = game_nb_neighbors(g3, 4, 4, BLACK) == 1;
    bool t9 = game_nb_neighbors(g4, 1, 1, BLACK) == 1;
    bool t10 = game_get_color(g3, 0, 0) == game_get_color(g4, 0, 0);
    bool t16 = game_nb_neighbors(g4, 1, 0, BLACK) == 1;
    game_delete(g3);
    game_delete(g4);
    game g5 = game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, CONS, cs, true, FULL_EXCLUDE);
    game g6 = game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, CONS, cs, true, ORTHO_EXCLUDE);
    bool t12 = game_nb_neighbors(g5, 0, 0, EMPTY) == 8;
    bool t13 = game_nb_neighbors(g6, 0, 0, EMPTY) == 4;
    game_play_move(g5, 0, 0, WHITE);
    game_play_move(g6, 0, 0, WHITE);
    bool t14 = game_nb_neighbors(g5, 0, 0, WHITE) == 1;
    bool t15 = game_nb_neighbors(g6, 0, 0, WHITE) == 1;
    game_delete(g1);
    game_delete(g2);
    game_delete(g5);
    game_delete(g6);
    if (t1 && !t2 && t3 && t4 && !t5 && !t6 && t7 && t8 && !t9 && t10 && t11 && t12 && t13 && !t14 && !t15 && t16) {
        return true;
    }
    return false;
}

bool test_game_copy()
{
    game g1 = game_default();
    game g2 = game_copy(g1);
    game g3 = game_default();
    game g4 = game_new_empty_ext(5, 5, true, ORTHO);
    game g5 = game_copy(g4);
    bool t1 = g1 == g2;
    bool t2 = game_equal(g1, g2);
    bool t3 = true;
    bool t4 = true;
    bool t5 = game_equal(g4, g5);
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0; j < DEFAULT_SIZE; j++) {
            if (game_get_color(g1, i, j) != game_get_color(g2, i, j)) {
                t3 = false;
            }
            if (game_get_constraint(g2, i, j) != game_get_constraint(g1, i, j)) {
                t4 = false;
            }
        }
    }
    bool t6 = game_equal(g2, g3);
    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    game_delete(g4);
    game_delete(g5);
    if (!t1 && t2 && t3 && t4 && t5 && t6) {
        return true;
    }
    return false;
}

bool test_game_restart()
{
    game g1 = game_default();
    game g2 = game_default();
    game g3 = game_default();
    bool t1 = game_equal(g1, g2);
    game_restart(g2);
    game_play_move(g3, 0, 0, WHITE);
    game_play_move(g3, 0, 1, BLACK);
    game_restart(g3);
    bool t2 = game_equal(g1, g2);
    bool t3 = game_equal(g1, g3);
    game_set_constraint(g2, 0, 0, 5);
    game_restart(g2);
    bool t4 = game_equal(g2, g3);
    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    if (t1 && t2 && t3 && !t4) {
        return true;
    }
    return false;
}

bool test_game_undo()
{
    game g1 = game_default();
    game g2 = game_default();
    game_undo(g1);
    bool t1 = game_equal(g1, g2);
    game_play_move(g1, 0, 0, BLACK);
    game_play_move(g1, 0, 1, WHITE);
    game_undo(g1);
    game_play_move(g2, 0, 3, BLACK);
    game_play_move(g2, 0, 3, WHITE);
    game_undo(g2);
    bool t0 = game_get_color(g2, 0, 3) == BLACK;
    bool t2 = game_equal(g1, g2);
    bool t5 = game_get_color(g1, 0, 1) == EMPTY;
    bool t3 = game_get_color(g1, 0, 0) == game_get_color(g2, 0, 0);
    bool t4 = game_get_color(g1, 0, 1) == game_get_color(g2, 0, 1);  // here
    game_delete(g1);
    game_delete(g2);
    if (t0 && t1 && !t2 && !t3 && t4 && t5) {
        return true;
    }
    return false;
}

bool test_game_redo()
{
    game g1 = game_default();
    game g2 = game_default();
    game_redo(g1);
    bool t1 = game_equal(g1, g2);
    game_play_move(g1, 0, 0, BLACK);
    game_play_move(g1, 0, 1, WHITE);
    game g3 = game_copy(g1);
    game_redo(g1);
    bool t5 = game_equal(g1, g3);
    game_undo(g1);
    bool t2 = game_equal(g1, g2);
    bool t3 = game_get_color(g1, 0, 1) == game_get_color(g2, 0, 1);
    game_redo(g1);
    bool t4 = game_get_color(g1, 0, 1) == game_get_color(g2, 0, 1);
    bool t6 = game_equal(g1, g3);
    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    if (t1 && !t2 && t3 && !t4 && t5 && t6) {
        return true;
    }
    return false;
}

int main(int argc, char* argv[])
{
    if (argc == 1) {
        fprintf(stderr, "No arguments detected.");
        return EXIT_FAILURE;
    }
    bool test = false;
    if (strcmp("dummy", argv[1]) == 0) {
        test = test_dummy();
    } else if (strcmp("game_equal", argv[1]) == 0) {
        test = test_game_equal();
    } else if (strcmp("game_get_color", argv[1]) == 0) {
        test = test_game_get_color();
    } else if (strcmp("game_get_constraint", argv[1]) == 0) {
        test = test_game_get_constraint();
    } else if (strcmp("game_nb_neighbors", argv[1]) == 0) {
        test = test_game_nb_neighbors();
    } else if (strcmp("game_copy", argv[1]) == 0) {
        test = test_game_copy();
    } else if (strcmp("game_restart", argv[1]) == 0) {
        test = test_game_restart();
    } else if (strcmp("game_undo", argv[1]) == 0) {
        test = test_game_undo();
    } else if (strcmp("game_redo", argv[1]) == 0) {
        test = test_game_redo();
    }
    if (test == true) {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}
