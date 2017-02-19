#include "screens.h"


void init_ncurses_graphics() {
    initscr();
    raw();
    nonl();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
}


int main() {
    init_ncurses_graphics();

    SCREEN_ID screen_cur = SC_TITLE;
    SCREEN_ID screen_next;

    while (1) {
        screen_next = screens[screen_cur]();

        if (screen_next == SC_EXIT) {
            break;
        }

        screen_cur = screen_next;
    }

    endwin();
    return 0;
}
