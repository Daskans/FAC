#include <stdio.h>
#include <stdlib.h>
#include "folt.h"
#ifdef _WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif




direction_t* read_ascii_direction() {
    int key;

    #ifdef _WIN32
    while (1) {
        if (_kbhit()) {
            key = _getch();

            if (key == 0xE0 || key == 0) {
                // Extended key
                key = _getch();

                if (key == UP_KEY) {
                    return UP;
                } else if (key == DOWN_KEY) {
                    preturn DOWN;
                }else if (key == LEFT_KEY) {
                    return LEFT;
                }else if (key == RIGHT_KEY) {
                    return RIGHT;
                }
            }
        }
    }
    #else
    initscr();  // Initialize ncurses
    keypad(stdscr, TRUE);  // Enable keypad mode

    while (1) {
        key = getch();

        if (key == KEY_UP) {
            printf("Up arrow key is pressed!\n");
        } else if (key == KEY_DOWN) {
            printf("down arrow key is pressed!\n");
        } else if (key == KEY_LEFT) {
            printf("left arrow key is pressed!\n");
        } else if (key == KEY_RIGHT) {
            printf("right arrow key is pressed!\n");
        }
    }

    endwin();  // Terminate ncurses
    #endif

}

void main(void) {
    detect_touche();
}