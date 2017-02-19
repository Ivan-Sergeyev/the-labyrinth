#ifndef TITLE_SCREEN_H_
#define TITLE_SCREEN_H_

#include <ncurses.h>

#include "screens.h"

enum TITLE_SCREEN_MENU_OPTIONS {TSM_START = 0, TSM_OPTIONS, TSM_QUIT, num_options};
const char* const menu_options[num_options] = {"Start", "Options", "Quit"};


void draw_menu(int highlight) {
    int height, width;
    getmaxyx(stdscr, height, width);

    int x = (width - num_options) / 2;
    int y = height / 2;

    for (int i = 0; i < num_options; ++i) {
        if (i == highlight) {
            attron(A_REVERSE);
            mvprintw(y, x, menu_options[i]);
            attroff(A_REVERSE);
        } else {
            mvprintw(y, x, menu_options[i]);
        }
        ++y;
    }
    refresh();
}


SCREEN_ID title_screen() {
    int key = 0;
    int exit = 0;
    int enter = 0;
    int highlight = 0;

    while (1) {
        draw_menu(highlight);

        key = getch();
        switch (key) {
            case 27:  // escape
                exit = 1;
                break;
            case KEY_ENTER:
            case 13:
            case 10: // enter
                switch (highlight) {
                    case TSM_START:
                        return SC_EXIT;  // todo: SC_GAME
                    case TSM_OPTIONS:
                        return SC_EXIT;  // todo: SC_OPTIONS
                    case TSM_QUIT:
                        exit = 1;
                        break;
                }
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % num_options;
                break;
            case KEY_UP:
                highlight = (num_options + highlight - 1) % num_options;
                break;
        }

        if (exit) {
            return SC_EXIT;
        }
    }
}

#endif  // TITLE_SCREEN_H_
