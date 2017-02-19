#ifndef TITLE_SCREEN_H_
#define TITLE_SCREEN_H_

#include <ncurses.h>


enum MENU_OPTIONS {START, OPTIONS, QUIT};
const int num_options = 3;
const char* const menu_options[num_options] = {"Start", "Options", "Quit"};


void draw_menu(int highlight) {
    int x = 70;
    int y = 20;

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


int title_screen() {
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
            case 10: // enter
            case 13:
                enter = 1;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % num_options;
                break;
            case KEY_UP:
                highlight = (num_options + highlight - 1) % num_options;
                break;
        }

        if (enter) {
            switch (highlight) {
                case START:
                    return 1;
                case OPTIONS:
                    return 2;
                case QUIT:
                    exit = 1;
                    break;
            }
        }
        if (exit) {
            return -1;
        }
    }
}

#endif  // TITLE_SCREEN_H_
