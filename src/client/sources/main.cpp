#include "../headers/screens.h"
#include "../../host/headers/gamestate.h"


void init_ncurses_graphics() {
    initscr();
    cbreak();
    nonl();
    keypad(stdscr, 1);
    curs_set(0);
}


void main_loop() {
    Gamestate *gamestate = nullptr;

    SCREEN_ID screen_cur = SCR_FIRST;
    SCREEN_ID screen_next;

    while (1) {
        clear();
        screen_next = screens[screen_cur](&gamestate);

        if (screen_next == SCR_EXIT) {
            if (gamestate) {
                delete gamestate;
            }
            break;
        }

        screen_cur = screen_next;
    }
}


void quit_ncurses_graphics() {
    endwin();
}


int main() {
    // todo : use App class (OOP vs functional programming)
    init_ncurses_graphics();
    main_loop();
    quit_ncurses_graphics();
    return 0;
}
