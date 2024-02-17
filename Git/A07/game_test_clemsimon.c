#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"

bool test_failure(game g)
{
    game_delete(g);
    return false;
}

int test_game_new_empty(game g)
{
    bool test = true;
    for (int row_number = 0; row_number < game_nb_rows(g); row_number++) {
        for (int colomn_number = 0; colomn_number < game_nb_cols(g); colomn_number++) {
            if (game_get_color(g, row_number, colomn_number) != EMPTY ||
                game_get_constraint(g, row_number, colomn_number) != UNCONSTRAINED) {
                test = false;
            }
        }
    }
    game_delete(g);
    game game_1 = game_default();
    game game_2 = game_new_empty();
    if (game_equal(game_1, game_2) != false) {
        test = false;
    }
    game_delete(game_1);
    game_delete(game_2);
    return test;
}

int test_game_new(constraint* constraints, color* colors)
{
    game game_1 = game_new(constraints, colors);
    uint array_number = 0;
    bool test = true;
    for (int i = 0; i < game_nb_rows(game_1); i++) {
        for (int j = 0; j < game_nb_cols(game_1); j++) {
            if (game_get_constraint(game_1, i, j) != constraints[array_number] &&
                game_get_constraint(game_1, i, j) < -1 && game_get_constraint(game_1, i, j) > 9) {
                test = false;
            }
            if (game_get_color(game_1, i, j) != colors[array_number] && game_get_color(game_1, i, j) < 0 &&
                game_get_color(game_1, i, j) > 2) {
                test = false;
            }
            array_number++;
        }
    }
    game game_2 = game_new(constraints, colors);
    if (game_equal(game_1, game_2) == false) {
        test = false;
    }
    game_delete(game_1);
    game_delete(game_2);
    return test;
}

int test_game_default(game g)
{
    if (g == NULL) {
        return false;
    }
    int array_number = 0;
    constraint default_constraints[DEFAULT_SIZE * DEFAULT_SIZE] = {0,  -1, -1, 3,  -1, -1, 5,  -1, -1, -1, -1, -1, 4,
                                                                   -1, 1,  6,  -1, 6,  3,  -1, -1, -1, -1, -1, -1};
    bool test = true;
    for (int row_number = 0; row_number < game_nb_rows(g); row_number++) {
        for (int column_number = 0; column_number < game_nb_cols(g); column_number++) {
            if (game_get_constraint(g, row_number, column_number) != default_constraints[array_number]) {
                test = false;
            }
            if (game_get_color(g, row_number, column_number) != EMPTY) {
                test = false;
            }
            if (game_get_status(g, row_number, column_number) != UNSATISFIED) {
                test = false;
            }
            array_number++;
        }
    }
    game game_2 = game_default_solution();
    if (game_equal(g, game_2) != false) {
        test = false;
    }
    game_delete(g);
    game_delete(game_2);
    return test;
}

int test_game_delete(game g)
{
    game_delete(g);
    game game_2 = game_new_empty();
    game_delete(game_2);
    game game_3 = game_default_solution();
    game_delete(game_3);
    return true;
}

int test_game_set_color(game g, uint i, uint j, color c)
{
    if (g == NULL) {
        return false;
    }
    bool test = true;
    if (i >= DEFAULT_SIZE || i < 0) {
        test = false;
    }
    if (j < 0 || j >= DEFAULT_SIZE) {
        test = false;
    }
    if (c < 0 || c > 2) {
        test = false;
    }
    constraint constraint = game_get_constraint(g, i, j);
    game_set_color(g, i, j, c);
    if (game_get_constraint(g, i, j) != constraint) {
        test = false;
    }
    if (game_get_color(g, i, j) != c) {
        test = false;
    }
    game_delete(g);
    return test;
}

int test_game_won(game g)
{
    if (game_won(g) != true && game_won(g) != false) {
        return test_failure(g);
    }
    bool test = true;
    bool test2 = true;
    if (game_won(g) == true) {
        for (int row_number = 0; row_number < game_nb_rows(g); row_number++) {
            for (int column_number = 0; column_number < game_nb_cols(g); column_number++) {
                if (game_get_color(g, row_number, column_number) != WHITE &&
                    game_get_color(g, row_number, column_number) != BLACK) {
                    test = false;
                }
                if (game_get_status(g, row_number, column_number) != SATISFIED) {
                    test = false;
                }
            }
        }
        game_play_move(g, 0, 0, EMPTY);
        if (game_won(g) == true) {
            test = false;
        }
    } else {
        for (int row_number = 0; row_number < game_nb_rows(g); row_number++) {
            for (int column_number = 0; column_number < game_nb_cols(g); column_number++) {
                if (game_get_color(g, row_number, column_number) != WHITE &&
                    game_get_color(g, row_number, column_number) != BLACK &&
                    game_get_color(g, row_number, column_number) != EMPTY) {
                    test2 = false;
                }
                if (game_get_status(g, row_number, column_number) != SATISFIED &&
                    game_get_status(g, row_number, column_number) != UNSATISFIED &&
                    game_get_status(g, row_number, column_number) != ERROR) {
                    test2 = false;
                }
            }
        }
    }
    game_delete(g);
    game game_1 = game_new_empty();
    if (game_won(game_1) == true) {
        return test_failure(g);
    }
    for (uint row_number = 0; row_number < game_nb_rows(game_1); row_number++) {
        for (uint column_number = 0; column_number < game_nb_cols(game_1); column_number++) {
            game_set_constraint(game_1, row_number, column_number, 0);
            game_play_move(game_1, row_number, column_number, WHITE);
        }
    }
    bool test3 = true;
    if (game_won(game_1) == false) {
        test3 = false;
    }
    game_delete(game_1);
    return test && test2 && test3;
}

/* *********************************************************** */

bool test_game_get_neighbourhood()
{
    uint nb_rows = 10;
    uint nb_cols = 10;
    constraint constraints[10 * 10] = {MIN_CONSTRAINT + 1};
    color array_of_colors[10 * 10] = {EMPTY};
    bool wrap = false;
    for (uint neigh = 0; neigh < ORTHO_EXCLUDE + 1; neigh++) {
        game g = game_new_ext(nb_rows, nb_cols, constraints, array_of_colors, wrap, neigh);
        if (game_get_neighbourhood(g) != neigh) {
            return test_failure(g);
        }
        if (game_nb_cols(g) != nb_cols || game_nb_rows(g) != nb_rows || game_is_wrapping(g) != wrap) {
            return test_failure(g);
        }
        if (game_is_wrapping(g) != true && game_is_wrapping(g) != false) {
            return test_failure(g);
        }
        game_delete(g);
    }
    return true;
}

bool test_game_new_ext(constraint* constraints, color* colors)
{
    uint nb_rows = 10;
    uint nb_cols = 10;
    bool wrap = false;
    neighbourhood neigh = FULL;
    game g = game_new_ext(nb_rows, nb_cols, constraints, colors, wrap, neigh);
    uint array_number = 0;
    for (int i = 0; i < game_nb_rows(g); i++) {
        for (int j = 0; j < game_nb_cols(g); j++) {
            if (game_get_constraint(g, i, j) != constraints[array_number] && game_get_constraint(g, i, j) < -1 &&
                game_get_constraint(g, i, j) > 9) {
                return test_failure(g);
            }
            if (game_get_color(g, i, j) != colors[array_number] && game_get_color(g, i, j) < 0 &&
                game_get_color(g, i, j) > 2) {
                return test_failure(g);
            }
            array_number++;
        }
    }
    if (game_get_neighbourhood(g) < FULL || game_get_neighbourhood(g) > ORTHO_EXCLUDE ||
        (game_is_wrapping(g) != true && game_is_wrapping(g) != false) || game_nb_rows(g) != nb_rows ||
        game_nb_cols(g) != nb_cols || game_is_wrapping(g) != wrap || game_get_neighbourhood(g) != neigh) {
        return test_failure(g);
    }
    game game_2 = game_new_ext(10, 10, constraints, colors, false, 0);
    bool test = true;
    if (game_equal(g, game_2) == false) {
        test = false;
    }
    game_delete(g);
    game_delete(game_2);
    return test;
}

bool test_game_new_empty_ext()
{
    uint nb_rows = 10;
    uint nb_cols = 10;
    bool wrap = true;
    neighbourhood neigh = FULL_EXCLUDE;
    game g = game_new_empty_ext(nb_rows, nb_cols, wrap, neigh);
    for (int row_number = 0; row_number < game_nb_rows(g); row_number++) {
        for (int column_number = 0; column_number < game_nb_cols(g); column_number++) {
            if (game_get_color(g, row_number, column_number) != EMPTY) {
                return test_failure(g);
            }
            if (game_get_constraint(g, row_number, column_number) != UNCONSTRAINED) {
                return test_failure(g);
            }
        }
    }
    if (game_get_neighbourhood(g) < FULL || game_get_neighbourhood(g) > ORTHO_EXCLUDE ||
        (game_is_wrapping(g) != true && game_is_wrapping(g) != false) || game_nb_rows(g) != nb_rows ||
        game_nb_cols(g) != nb_cols || game_is_wrapping(g) != wrap || game_get_neighbourhood(g) != neigh) {
        return test_failure(g);
    }
    game_delete(g);
    game game_1 = game_default();
    game game_2 = game_new_empty_ext(nb_rows, nb_cols, wrap, neigh);
    bool test = true;
    if (game_equal(game_1, game_2) != false) {
        test = false;
    }
    game_delete(game_1);
    game_delete(game_2);
    return test;
}

/* *********************************************************** */

int test_dummy() { return true; }

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return EXIT_FAILURE;
    }
    bool ok = false;
    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    if (strcmp("dummy", argv[1]) == 0) {
        ok = test_dummy();
    } else if (strcmp("game_new_empty", argv[1]) == 0) {
        game g = game_new_empty();
        ok = test_game_new_empty(g);
    } else if (strcmp("game_new", argv[1]) == 0) {
        constraint L[DEFAULT_SIZE * DEFAULT_SIZE] = {MIN_CONSTRAINT + 1};
        color L2[DEFAULT_SIZE * DEFAULT_SIZE] = {EMPTY};
        ok = test_game_new(L, L2);
    } else if (strcmp("game_default", argv[1]) == 0) {
        game g = game_default();
        ok = test_game_default(g);
    } else if (strcmp("game_won", argv[1]) == 0) {
        game g = game_default_solution();
        game g2 = game_default();
        ok = test_game_won(g) && test_game_won(g2);
    } else if (strcmp("game_delete", argv[1]) == 0) {
        game g = game_default_solution();
        ok = test_game_delete(g);
    } else if (strcmp("game_set_color", argv[1]) == 0) {
        ok = test_game_set_color(game_default(), 0, 4, WHITE);
    } else if (strcmp("game_get_neighbourhood", argv[1]) == 0) {
        ok = test_game_get_neighbourhood();
    } else if (strcmp("game_new_ext", argv[1]) == 0) {
        constraint L[10 * 10] = {MIN_CONSTRAINT + 1};
        color L2[10 * 10] = {EMPTY};
        ok = test_game_new_ext(L, L2);
    } else if (strcmp("game_new_empty_ext", argv[1]) == 0) {
        ok = test_game_new_empty_ext();
    } else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (ok == true) {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}
