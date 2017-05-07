#include <ncurses.h>

#include "../headers/app.h"


void App::_ncurses_init() {
    initscr();
    cbreak();
    nonl();
    keypad(stdscr, 1);
    curs_set(0);
}

void App::_ncurses_quit() {
    endwin();
}

App::App(GeneralScreen *screen_first) :
        _screen_cur(screen_first) {
    _ncurses_init();
}

App::~App() {
    _ncurses_quit();
}

int App::run() {
    GeneralScreen *screen_next;
    while (1) {
        clear();
        screen_next = _screen_cur->loop();

        if (screen_next == nullptr) {
            break;
        }

        delete _screen_cur;
        _screen_cur = screen_next;
    }

    return 0;
}
