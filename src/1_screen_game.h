#ifndef SRC_1_SCREEN_GAME_H_
#define SRC_1_SCREEN_GAME_H_

#include <ncurses.h>

#include "screens.h"

SCREEN_ID game() {
    int key;
    int exit = 0;

    while (1) {
        key = getch();
        switch (key) {
            case 27:  // escape
                exit = 1;
                break;
        }

        if (exit) {
            return SC_EXIT;
        }
    }
}

#endif  // SRC_1_SCREEN_GAME_H_
