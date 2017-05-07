#include <iostream>
#include <ncurses.h>

#include "../headers/app.h"


void _ncurses_init() {
    initscr();
    cbreak();
    nonl();
    keypad(stdscr, 1);
    curs_set(0);
}

void _ncurses_quit() {
    endwin();
}

App::App(GeneralScreen *screen_first) :
        _gamestate(nullptr),
        _screen_cur(screen_first) {
    _gamestate = new Gamestate* [1];
    _ncurses_init();
}

App::~App() {
    if (_gamestate) {
        delete_gamestate();
    }
    delete _gamestate;
    _ncurses_quit();
}

int App::run() {
    GeneralScreen *screen_next;
    while (1) {
        clear();
        std::cerr << "ok start loop\n";
        screen_next = _screen_cur->loop(_gamestate);
        std::cerr << "ok loop\n";

        if (screen_next == nullptr) {
            break;
        }

        std::cerr << "ok screen next\n";
        delete _screen_cur;
        std::cerr << "ok delete screen cur\n";
        _screen_cur = screen_next;
    }

    return 0;
}

void App::new_gamestate() {
    if (_gamestate) {
        delete_gamestate();
    }
    *_gamestate = new Gamestate(1);
}

void App::delete_gamestate() {
    delete *_gamestate;
}
