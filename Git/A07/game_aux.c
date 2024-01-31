#include "game_aux.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_struct.h"

void game_print(cgame g)
{
    if (g == NULL) {
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "   0 1 2 3 4\n");
    fprintf(stdout, "     ----------\n");
    for (int row_number = 0; row_number < DEFAULT_SIZE; row_number++) {
        fprintf(stdout, " %d |", row_number);
        for (int column_number = 0; column_number < DEFAULT_SIZE; column_number++) {
            constraint constraint = game_get_constraint(g, row_number, column_number);
            color color = game_get_color(g, row_number, column_number);
            if (color == EMPTY && constraint != -1) {
                fprintf(stdout, "%d ", constraint);
            }
            if (constraint == -1) {
                if (color == BLACK) {
                    fprintf(stdout, "■ ");
                } else if (color == WHITE) {
                    fprintf(stdout, "□ ");
                } else {
                    fprintf(stdout, "  ");
                }
            } else if (constraint == 0) {
                if (color == BLACK) {
                    fprintf(stdout, "🄌 ");
                } else if (color == WHITE) {
                    fprintf(stdout, "🄋 ");
                }
            } else if (constraint == 1) {
                if (color == BLACK) {
                    fprintf(stdout, "➊ ");
                } else if (color == WHITE) {
                    fprintf(stdout, "➀ ");
                }
            } else if (constraint == 2) {
                if (color == BLACK) {
                    fprintf(stdout, "➋ ");
                } else if (color == WHITE) {
                    fprintf(stdout, "➁ ");
                }
            } else if (constraint == 3) {
                if (color == BLACK) {
                    fprintf(stdout, "➌ ");
                } else if (color == WHITE) {
                    fprintf(stdout, "➂ ");
                }
            } else if (constraint == 4) {
                if (color == BLACK) {
                    fprintf(stdout, "➍ ");
                } else if (color == WHITE) {
                    fprintf(stdout, "➃ ");
                }
            } else if (constraint == 5) {
                if (color == BLACK) {
                    fprintf(stdout, "➎ ");
                } else if (color == WHITE) {
                    fprintf(stdout, "➄ ");
                }
            } else if (constraint == 6) {
                if (color == BLACK) {
                    fprintf(stdout, "➏ ");
                } else if (color == WHITE) {
                    fprintf(stdout, "➅ ");
                }
            } else if (constraint == 7) {
                if (color == BLACK) {
                    fprintf(stdout, "➐ ");
                } else if (color == WHITE) {
                    fprintf(stdout, "➆ ");
                }
            } else if (constraint == 8) {
                if (color == BLACK) {
                    fprintf(stdout, "➑ ");
                } else if (color == WHITE) {
                    fprintf(stdout, "➇ ");
                }
            } else if (constraint == 9) {
                if (color == BLACK) {
                    fprintf(stdout, "➒ ");
                } else if (color == WHITE) {
                    fprintf(stdout, "➈ ");
                }
            }
            if (column_number == DEFAULT_SIZE - 1) {
                fprintf(stdout, "|\n");
            }
        }
    }
    fprintf(stdout, "     ----------\n");
}

game game_default(void)
{
    constraint array_of_constraints[DEFAULT_SIZE * DEFAULT_SIZE] = {0,  -1, -1, 3,  -1, -1, 5,  -1, -1, -1, -1, -1, 4,
                                                                    -1, 1,  6,  -1, 6,  3,  -1, -1, -1, -1, -1, -1};
    color array_of_colors[DEFAULT_SIZE * DEFAULT_SIZE] = {EMPTY};
    game g = game_new(array_of_constraints, array_of_colors);
    if (g == NULL) {
        fprintf(stderr, "game not created, error\n");
        game_delete(g);
        exit(EXIT_FAILURE);
    }
    return g;
}

game game_default_solution(void)
{
    constraint array_of_constraints[DEFAULT_SIZE * DEFAULT_SIZE] = {0,  -1, -1, 3,  -1, -1, 5,  -1, -1, -1, -1, -1, 4,
                                                                    -1, 1,  6,  -1, 6,  3,  -1, -1, -1, -1, -1, -1};
    color array_of_colors[DEFAULT_SIZE * DEFAULT_SIZE] = {WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE,
                                                          BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE,
                                                          WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, WHITE};
    game g = game_new(array_of_constraints, array_of_colors);
    if (g == NULL) {
        fprintf(stderr, "game not created, error\n");
        game_delete(g);
        exit(EXIT_FAILURE);
    }
    return g;
}