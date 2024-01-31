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

bool test_dummy() { return true; }

bool test_game_set_constraint()
{
    for (uint i = 0; i <= 4; i++) {
        for (uint j = 0; j <= 4; j++) {
            for (constraint n = -1; n <= MAX_CONSTRAINT; n++) {
                game g = game_new_empty();
                if (g == NULL) {
                    return test_failure(g);
                }
                game_set_constraint(g, i, j, n);
                if (i >= DEFAULT_SIZE || i < 0) {
                    return test_failure(g);
                }
                if (j >= DEFAULT_SIZE || j < 0) {
                    return test_failure(g);
                }
                if (n < MIN_CONSTRAINT || n > MAX_CONSTRAINT) {
                    return test_failure(g);
                }
                game_delete(g);
            }
        }
    }
    game g = game_new_empty();
    color c = game_get_color(g, 0, 0);
    game_set_constraint(g, 0, 0, 9);
    if (c != game_get_color(g, 0, 0)) {
        return test_failure(g);
    }
    if (game_get_constraint(g, 0, 0) != 9) {
        return test_failure(g);
    }
    game_set_constraint(g, 0, 1, 0);
    game_play_move(g, 0, 0, BLACK);
    status stat = game_get_status(g, 0, 1);
    if (stat != ERROR) {
        return test_failure(g);
    }
    game_delete(g);
    return true;
}

bool test_game_play_move()
{
    for (uint i = 0; i <= 4; i++) {
        for (uint j = 0; j <= 4; j++) {
            for (color c = EMPTY; c <= BLACK; c++) {
                game g = game_new_empty();
                game_play_move(g, i, j, c);
                if (g == NULL) {
                    return test_failure(g);
                }
                status stat = game_get_status(g, i, j);
                if (stat == ERROR) {
                    return test_failure(g);
                }
                color c2 = game_get_color(g, i, j);
                if (c2 != c) {
                    return test_failure(g);
                }
                game_delete(g);
            }
        }
    }
    game g = game_new_empty();
    game_set_constraint(g, 0, 0, 4);
    if (game_get_status(g, 0, 0) != UNSATISFIED) {
        return test_failure(g);
    }
    game_play_move(g, 0, 0, BLACK);
    if (game_get_status(g, 0, 0) != UNSATISFIED) {
        return test_failure(g);
    }
    game_play_move(g, 0, 1, BLACK);
    if (game_get_status(g, 0, 0) != UNSATISFIED) {
        return test_failure(g);
    }
    game_play_move(g, 1, 1, BLACK);
    if (game_get_status(g, 0, 0) != UNSATISFIED) {
        return test_failure(g);
    }
    game_play_move(g, 1, 0, BLACK);
    if (game_get_status(g, 0, 0) != SATISFIED) {
        return test_failure(g);
    }
    game_delete(g);
    return true;
}

bool test_game_default_solution()
{
    game g = game_default_solution();
    uint cpt = 0;
    constraint CONS[DEFAULT_SIZE * DEFAULT_SIZE] = {0,  -1, -1, 3,  -1, -1, 5,  -1, -1, -1, -1, -1, 4,
                                                    -1, 1,  6,  -1, 6,  3,  -1, -1, -1, -1, -1, -1};
    color SOLUCE[DEFAULT_SIZE * DEFAULT_SIZE] = {WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE,
                                                 BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE,
                                                 WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, WHITE};
    for (uint i = 0; i < DEFAULT_SIZE; i++) {
        for (uint j = 0; j < DEFAULT_SIZE; j++) {
            if (game_get_color(g, i, j) != SOLUCE[cpt]) {
                return test_failure(g);
            }
            if (game_get_status(g, i, j) != SATISFIED) {
                return test_failure(g);
            }
            if (game_get_constraint(g, i, j) != CONS[cpt]) {
                return test_failure(g);
            }
            cpt++;
        }
    }
    if (game_won(g) != true) {
        return test_failure(g);
    }
    game_delete(g);
    return true;
}

bool test_game_print()
{
    game g = game_new_empty();
    if (g == NULL) {
        return test_failure(g);
    }
    game_print(g);
    game_delete(g);
    return true;
}

bool test_game_get_status()
{
    for (uint i = 0; i <= 4; i++) {
        for (uint j = 0; j <= 4; j++) {
            game g = game_new_empty();
            if (g == NULL) {
                return test_failure(g);
            }
            if (i >= DEFAULT_SIZE || i < 0) {
                return test_failure(g);
            }
            if (j >= DEFAULT_SIZE || j < 0) {
                return test_failure(g);
            }
            status stat = game_get_status(g, i, j);
            if (stat == ERROR) {
                return test_failure(g);
            }
            game_delete(g);
        }
    }
    game g = game_new_empty();
    game g2 = game_default_solution();
    game g3 = game_new_empty_ext(5, 5, true, FULL);
    game_set_constraint(g3, 0, 0, 1);
    game_play_move(g3, 4, 0, BLACK);
    game_play_move(g3, 0, 1, WHITE);
    game_play_move(g3, 0, 0, WHITE);
    game_play_move(g3, 4, 1, WHITE);
    game_play_move(g3, 0, 4, WHITE);
    game_play_move(g3, 4, 4, WHITE);
    game_play_move(g3, 1, 1, WHITE);
    game_play_move(g3, 1, 0, WHITE);
    game_play_move(g3, 1, 4, WHITE);
    status stat_g3 = game_get_status(g3, 0, 0);
    if (stat_g3 != SATISFIED) {
        return test_failure(g3);
    }
    game_set_constraint(g, 0, 0, 4);
    game_play_move(g, 0, 0, BLACK);
    game_play_move(g, 1, 0, BLACK);
    game_play_move(g, 0, 1, BLACK);
    game_play_move(g, 1, 1, BLACK);
    status stat = game_get_status(g, 0, 0);
    if (stat != SATISFIED) {
        game_delete(g);
        return test_failure(g2);
    }
    if (game_get_status(g2, 0, 0) != SATISFIED) {
        game_delete(g);
        return test_failure(g2);
    }
    game_play_move(g2, 1, 0, BLACK);
    if (game_get_status(g2, 0, 0) == SATISFIED) {
        game_delete(g);
        return test_failure(g2);
    }
    game_delete(g);
    game_delete(g2);
    game_delete(g3);
    return true;
}

bool test_game_get_next_square()
{
    game g = game_new_empty();
    uint pi_next;
    uint pj_next;
    if (game_get_next_square(g, 2, 2, UP, &pi_next, &pj_next) != true || pi_next != 1 || pj_next != 2) {
        return test_failure(g);
    }
    if (game_get_next_square(g, 4, 4, DOWN_RIGHT, &pi_next, &pj_next) != false) {
        return test_failure(g);
    }
    if (game_get_next_square(g, 4, 4, HERE, &pi_next, &pj_next) != true || pi_next != 4 || pj_next != 4) {
        return test_failure(g);
    }
    for (uint i = 0; i < game_nb_rows(g); i++) {
        for (uint j = 0; j < game_nb_cols(g); j++) {
            if (i >= DEFAULT_SIZE || i < 0) {
                return test_failure(g);
            }
            if (j >= DEFAULT_SIZE || j < 0) {
                return test_failure(g);
            }
            if (game_get_next_square(g, i, j, HERE, &pi_next, &pj_next) != true || pi_next != i || pj_next != j) {
                return test_failure(g);
            }
        }
    }
    if (game_get_next_square(g, 4, 4, DOWN_RIGHT, &pi_next, &pj_next) != false) {
        return test_failure(g);
    }
    if (game_get_next_square(g, 0, 4, DOWN_RIGHT, &pi_next, &pj_next) != false) {
        return test_failure(g);
    }
    if (game_get_next_square(g, 4, 0, DOWN_RIGHT, &pi_next, &pj_next) != false) {
        return test_failure(g);
    }
    if (game_get_next_square(g, 0, 0, DOWN_RIGHT, &pi_next, &pj_next) != true || pi_next != 1 || pj_next != 1) {
        return test_failure(g);
    }
    for (direction dir = HERE; dir <= DOWN_RIGHT; dir++) {
        if (game_get_next_square(g, 2, 2, dir, &pi_next, &pj_next) != true) {
            return test_failure(g);
        }
    }
    game_delete(g);
    game g1 = game_new_empty_ext(8, 5, true, FULL);
    if (game_get_next_square(g1, 0, 0, UP_LEFT, &pi_next, &pj_next) != true || pi_next != 7 || pj_next != 4) {
        return test_failure(g1);
    }
    game_delete(g1);
    for (neighbourhood n = FULL; n <= ORTHO_EXCLUDE; n++) {
        game g = game_new_empty_ext(5, 5, true, n);
        uint pi_next;
        uint pj_next;
        if (game_get_next_square(g, 0, 0, UP_LEFT, &pi_next, &pj_next) != true || pi_next != 4 || pj_next != 4) {
            return test_failure(g);
        }
        game_delete(g);
    }
    for (neighbourhood n = FULL; n <= ORTHO_EXCLUDE; n++) {
        game g = game_new_empty_ext(5, 5, false, n);
        uint pi_next;
        uint pj_next;
        if (game_get_next_square(g, 0, 0, UP_LEFT, &pi_next, &pj_next) != false) {
            return test_failure(g);
        }
        game_delete(g);
    }
    for (neighbourhood n = FULL; n <= ORTHO_EXCLUDE; n++) {
        game g = game_new_empty_ext(8, 5, true, n);
        uint pi_next;
        uint pj_next;
        if (game_get_next_square(g, 0, 0, UP_LEFT, &pi_next, &pj_next) != true) {
            return test_failure(g);
        }
        if (pi_next != 7 || pj_next != 4) {
            return test_failure(g);
        }
        if (game_get_next_square(g, 4, 0, DOWN_LEFT, &pi_next, &pj_next) != true) {
            return test_failure(g);
        }
        if (pi_next != 5 || pj_next != 4) {
            return test_failure(g);
        }
        game_delete(g);
    }
    for (neighbourhood n = FULL; n <= ORTHO_EXCLUDE; n++) {
        game g = game_new_empty_ext(8, 5, false, n);
        uint pi_next;
        uint pj_next;
        if (game_get_next_square(g, 0, 0, UP_LEFT, &pi_next, &pj_next) != false) {
            return test_failure(g);
        }
        if (game_get_next_square(g, 4, 0, DOWN_LEFT, &pi_next, &pj_next) != false) {
            return test_failure(g);
        }
        game_delete(g);
    }

    return true;
}

bool test_game_nb_rows()
{
    constraint CONS[DEFAULT_SIZE * DEFAULT_SIZE] = {0,  -1, -1, 3,  -1, -1, 5,  -1, -1, -1, -1, -1, 4,
                                                    -1, 1,  6,  -1, 6,  3,  -1, -1, -1, -1, -1, -1};
    color SOLUCE[DEFAULT_SIZE * DEFAULT_SIZE] = {WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE,
                                                 BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE,
                                                 WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, WHITE};
    constraint CONS1[6 * 5] = {0, -1, -1, 3, -1, -1, 5,  -1, -1, -1, -1, -1, 4, -1, 1,
                               6, -1, 6,  3, -1, -1, -1, -1, -1, -1, 4,  -1, 4, -1, 1};
    color SOLUCE1[6 * 5] = {WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, BLACK,
                            BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, WHITE,
                            BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, WHITE, WHITE, WHITE};
    for (neighbourhood i = FULL; i <= ORTHO_EXCLUDE; i++) {
        game g0 = game_new_ext(5, 5, CONS, SOLUCE, false, i);
        game g1 = game_new_ext(5, 5, CONS, SOLUCE, true, i);
        game g2 = game_new(CONS, SOLUCE);
        if (game_nb_rows(g0) != 5 || game_nb_rows(g1) != 5 || game_nb_rows(g2) != 5) {
            game_delete(g0);
            game_delete(g1);
            return test_failure(g2);
        }
        game_delete(g0);
        game_delete(g1);
        game_delete(g2);
    }
    for (neighbourhood i = FULL; i <= ORTHO_EXCLUDE; i++) {
        game g0 = game_new_ext(6, 5, CONS1, SOLUCE1, false, i);
        if (game_nb_rows(g0) != 6) {
            return test_failure(g0);
        }
        game_delete(g0);
    }
    return true;
}

bool test_game_nb_cols()
{
    constraint CONS[DEFAULT_SIZE * DEFAULT_SIZE] = {0,  -1, -1, 3,  -1, -1, 5,  -1, -1, -1, -1, -1, 4,
                                                    -1, 1,  6,  -1, 6,  3,  -1, -1, -1, -1, -1, -1};
    color SOLUCE[DEFAULT_SIZE * DEFAULT_SIZE] = {WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE,
                                                 BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE,
                                                 WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, WHITE};
    constraint CONS1[6 * 5] = {0, -1, -1, 3, -1, -1, 5,  -1, -1, -1, -1, -1, 4, -1, 1,
                               6, -1, 6,  3, -1, -1, -1, -1, -1, -1, 4,  -1, 4, -1, 1};
    color SOLUCE1[6 * 5] = {WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, BLACK,
                            BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, WHITE,
                            BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, WHITE, WHITE, WHITE};
    for (neighbourhood i = FULL; i <= ORTHO_EXCLUDE; i++) {
        game g0 = game_new_ext(5, 5, CONS, SOLUCE, false, i);
        game g1 = game_new_ext(5, 5, CONS, SOLUCE, true, i);
        game g2 = game_new(CONS, SOLUCE);
        if (game_nb_cols(g0) != 5 || game_nb_cols(g1) != 5 || game_nb_cols(g2) != 5) {
            game_delete(g0);
            game_delete(g1);
            return test_failure(g2);
        }
        game_delete(g0);
        game_delete(g1);
        game_delete(g2);
    }
    for (neighbourhood i = FULL; i <= ORTHO_EXCLUDE; i++) {
        game g0 = game_new_ext(5, 6, CONS1, SOLUCE1, false, i);
        if (game_nb_cols(g0) != 6) {
            return test_failure(g0);
        }
        game_delete(g0);
    }
    return true;
}

bool test_game_is_wrapping()
{
    for (neighbourhood n = FULL; n <= ORTHO_EXCLUDE; n++) {
        game g0 = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, true, n);
        game g1 = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, n);
        if (game_is_wrapping(g0) != true) {
            game_delete(g1);
            return test_failure(g0);
        }
        if (game_is_wrapping(g1) != false) {
            game_delete(g0);
            return test_failure(g1);
        }
        game_delete(g0);
        game_delete(g1);
    }
    return true;
}

int main(int argc, char* argv[])
{
    bool state = false;
    if (argv[1] == NULL) {
        state = false;
    }
    if (strcmp("dummy", argv[1]) == 0) {
        state = test_dummy();
    } else if (strcmp("game_set_constraint", argv[1]) == 0) {
        state = test_game_set_constraint();
    } else if (strcmp("game_play_move", argv[1]) == 0) {
        state = test_game_play_move();
    } else if (strcmp("game_default_solution", argv[1]) == 0) {
        state = test_game_default_solution();
    } else if (strcmp("game_print", argv[1]) == 0) {
        state = test_game_print();
    } else if (strcmp("game_get_status", argv[1]) == 0) {
        state = test_game_get_status();
    } else if (strcmp("game_get_next_square", argv[1]) == 0) {
        state = test_game_get_next_square();
    } else if (strcmp("game_nb_rows", argv[1]) == 0) {
        state = test_game_nb_rows();
    } else if (strcmp("game_nb_cols", argv[1]) == 0) {
        state = test_game_nb_cols();
    } else if (strcmp("game_is_wrapping", argv[1]) == 0) {
        state = test_game_is_wrapping();
    } else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (state == true) {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}