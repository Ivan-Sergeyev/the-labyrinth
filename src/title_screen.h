#ifndef SRC_TITLE_SCREEN_H_
#define SRC_TITLE_SCREEN_H_

#include <ncurses.h>

#include "screens.h"

enum TITLE_SCREEN_MENU_OPTIONS {
    TSM_START = 0, TSM_OPTIONS, TSM_QUIT, TSM_NUM_OPTIONS
};
const char* const menu_options[TSM_NUM_OPTIONS] = {"Start", "Options", "Quit"};


void draw_menu(int highlight) {
    int height, width;
    getmaxyx(stdscr, height, width);

    int x = (width - TSM_NUM_OPTIONS) / 2;
    int y = height / 2;

    for (int i = 0; i < TSM_NUM_OPTIONS; ++i) {
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
            case 10:  // enter
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
                highlight = (highlight + 1) % TSM_NUM_OPTIONS;
                break;
            case KEY_UP:
                highlight = (TSM_NUM_OPTIONS + highlight - 1) % TSM_NUM_OPTIONS;
                break;
        }

        if (exit) {
            return SC_EXIT;
        }
    }
}

#endif  // SRC_TITLE_SCREEN_H_
