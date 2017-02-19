#include "title_screen.h"


enum SCREENS {SC_EXIT = -1, SC_TITLE};
const int num_screens = 1;
int (* const screens[num_screens])() = {title_screen};


int main() {
    initscr();
    raw();
    nonl();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);

    int (*current_screen)() = screens[SC_TITLE];
    int transition;

    while (1) {
        transition = current_screen() + 1;

        if (!transition) {
            break;
        }

        break;
        current_screen = screens[transition];
    }

    endwin();
    return 0;
}
