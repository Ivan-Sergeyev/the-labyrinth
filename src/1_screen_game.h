#ifndef SRC_1_SCREEN_GAME_H_
#define SRC_1_SCREEN_GAME_H_

#include <string.h>
#include <ncurses.h>

#include "gamestate.h"
#include "screens.h"
#include "player.h"


bool process_input(char *str, int len) {
    return !strncmp(str, "exit", len);
}


SCREEN_ID game() {
    echo();

    int scr_h, scr_w;
    getmaxyx(stdscr, scr_h, scr_w);

    int msg_box_y = 2;
    int msg_box_x = scr_w / 2 + 1;
    int msg_box_h = scr_h - 2 * msg_box_y;
    int msg_box_w = scr_w / 2 - 2;

    WINDOW *msg_box = newwin(msg_box_h, msg_box_w,
                             msg_box_y, msg_box_x);

    int msg_in_y = msg_box_y + msg_box_h - 4;
    int msg_in_x = msg_box_x + 1;
    int msg_in_h = 3;
    int msg_in_w = msg_box_w - 2;

    WINDOW *msg_in = newwin(msg_in_h, msg_in_w,
                            msg_in_y, msg_in_x);

    int msg_out_y = msg_box_y + 1;
    int msg_out_x = msg_box_x + 1;
    int msg_out_h = msg_box_h - msg_in_h - 2;
    int msg_out_w = msg_box_w - 2;

    WINDOW *msg_out = newwin(msg_out_h, msg_out_w,
                             msg_out_y, msg_out_x);

    int key;
    bool exit = false;

    int MAX_MSG_LEN = msg_in_w - 4;
    int MAX_HISTORY_LEN = msg_out_h - 2;

    char str[MAX_MSG_LEN];
    char msg_history[MAX_HISTORY_LEN][MAX_MSG_LEN];

    str[0] = 0;
    for (int i = 0; i < MAX_HISTORY_LEN; ++i) {
        msg_history[i][0] = 0;
    }

    while (1) {
        refresh();

        wclear(msg_box);
        box(msg_box, 0, 0);
        wrefresh(msg_box);

        wclear(msg_out);
        box(msg_out, 0, 0);
        for (int i = 0; i < MAX_HISTORY_LEN; ++i) {
            mvwprintw(msg_out, msg_out_h - 2 - i, 1, msg_history[i]);
        }
        wrefresh(msg_out);

        wclear(msg_in);
        box(msg_in, 0, 0);
        mvwprintw(msg_in, 1, 1, "> ");
        wrefresh(msg_in);

        wgetnstr(msg_in, str, MAX_MSG_LEN);

        exit = process_input(str, MAX_MSG_LEN);

        if (exit) {
            delwin(msg_in);
            delwin(msg_out);
            delwin(msg_box);
            return SC_EXIT;
        }

        for (int i = MAX_HISTORY_LEN - 1; i > 0; --i) {
            strncpy(msg_history[i], msg_history[i - 1], MAX_MSG_LEN);
        }
        strncpy(msg_history[0], str, MAX_MSG_LEN);
    }
}

#endif  // SRC_1_SCREEN_GAME_H_
