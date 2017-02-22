#include "../headers/screens.h"


void init_ncurses_graphics() {
    initscr();
    cbreak();
    nonl();
    keypad(stdscr, 1);
    curs_set(0);
}


void main_loop() {
    SCREEN_ID screen_cur = SC_FIRST;
    SCREEN_ID screen_next;

    while (1) {
        clear();
        screen_next = screens[screen_cur]();

        if (screen_next == SC_EXIT) {
            break;
        }

        screen_cur = screen_next;
    }
}


void quit_ncurses_graphics() {
    endwin();
}


int main() {
    init_ncurses_graphics();
    main_loop();
    quit_ncurses_graphics();
    return 0;
}
