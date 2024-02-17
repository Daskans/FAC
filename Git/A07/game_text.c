#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"

int main(void)
{
    game g = game_default();
    while (game_won(g) == false) {
        game_print(g);
        char c;
        uint i, j;

        scanf(" %c", &c);
        if (c == 'h') {
            printf(
                "- press 'w' <i> <j> to set square (i, j) white\n- press 'b' <i> "
                "<j> to set square (i, j) black\n- press 'e' "
                "<i> <j> to set square (i, j) empty\n");
            printf("- press 'r' to restart\n- press 'q' to quit\n");
            printf("- press 'z' to undo your last move\n");
            printf("- press 'y' to redo your last undone move\n\n");
        } else if (c == 'r') {
            game_restart(g);
        } else if (c == 'q') {
            printf("Shame\n");
            return EXIT_SUCCESS;
        } else if (c == 'w' || c == 'b' || c == 'e') {
            scanf("%d %d", &i, &j);
            if (game_get_status(g, i, j) == 0) {
                printf("Error\n");
            }
            if (i < DEFAULT_SIZE && j < DEFAULT_SIZE) {
                if (c == 'w') {
                    game_play_move(g, i, j, WHITE);
                } else if (c == 'b') {
                    game_play_move(g, i, j, BLACK);
                } else if (c == 'e') {
                    game_play_move(g, i, j, EMPTY);
                }
            }
        } else if (c == 'z') {
            game_undo(g);
        } else if (c == 'y') {
            game_redo(g);
        }
    }
    game_print(g);
    printf("Congratulation\n");
    return EXIT_SUCCESS;
}