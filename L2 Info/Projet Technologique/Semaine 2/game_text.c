#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "game_aux.h"

void game_print_error(game g) {
    for (int i=0; i<DEFAULT_SIZE; i++) {
        for (int j=0; j<DEFAULT_SIZE; j++) {
            game_get_status(g, i, j);
        }
    }
}

void print_game_help() {
    printf("- press 'w <i> <j>' to set square (i,j) white\n");
    printf("- press 'b <i> <j>' to set square (i,j) black\n");
    printf("- press 'e <i> <j>' to set square (i,j) empty\n");
    printf("- press 'r' to restart\n");
    printf("- press 'q' to quit\n");
}

int main(void) {
    game g=game_default();
    while (game_won(g)==false) {
        game_print(g);
        game_print_error(g);
        char choice;
        int i,j;
        printf("enter a command [h for help] : \n");
        scanf(" %c", &choice);
        if (choice=='h') {
            printf("> action: help\n");
            print_game_help();
        }
        else if (choice=='r') {
            printf("> action: restart\n");
            game_restart(g);
        }
        else if (choice=='q') {
            printf("> action: quit\n");
            printf("SHAME !\n");
            game_delete(g);
            return EXIT_SUCCESS;
        }
        else if (choice=='w'||choice=='b'||choice=='e') {
            printf("chose a location [i j]; i is down/up and j is left/right.\n");
            scanf(" %d %d", &i, &j);
            if (i>=0 && j>=0 && i<DEFAULT_SIZE && j<DEFAULT_SIZE) {
                if (choice=='w') {
                    printf("> action: white %d %d\n", i, j);
                    game_play_move(g, i, j, WHITE);
                }
                else if (choice=='b') {
                    printf("> action: black %d %d\n", i, j);
                    game_play_move(g, i, j, BLACK);
                }
                else if (choice=='e') {
                    printf("> action: empty %d %d\n", i, j);
                    game_play_move(g, i, j, EMPTY);
                }
            } else {
                printf("/!\\ please put a correct location /!\\ \n");
            }

        }
        else {
            printf("incorrect command, please retry\n");
        }
    }
    game_print(g);
    printf("A congratulation, it's a celebration !");
    game_delete(g);
    return EXIT_SUCCESS;
}

