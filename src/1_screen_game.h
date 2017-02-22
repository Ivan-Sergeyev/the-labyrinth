#ifndef SRC_1_SCREEN_GAME_H_
#define SRC_1_SCREEN_GAME_H_

#include <string.h>
#include <ncurses.h>

#include "screens.h"
#include "message_windows.h"

#include "gamestate.h"
#include "player.h"


SCREEN_ID game() {
    echo();

    int scr_h, scr_w;
    getmaxyx(stdscr, scr_h, scr_w);

    int mb_y = 2;
    int mb_x = scr_w / 2 + 1;
    int mb_h = scr_h - 2 * mb_y;
    int mb_w = scr_w / 2 - 2;

    int mi_y = mb_y + mb_h - 4;
    int mi_x = mb_x + 1;
    int mi_h = 3;
    int mi_w = mb_w - 2;

    int mh_y = mb_y + 1;
    int mh_x = mb_x + 1;
    int mh_h = mb_h - mi_h - 2;
    int mh_w = mb_w - 2;

    int _MAX_MSG_LEN = mi_w - 4 + 1;
    int _MAX_HISTORY_LEN = mh_h - 2;

    BoxWindow _msg_box(mb_h, mb_w, mb_y, mb_x);

    MessageInputBox _msg_in(mi_h, mi_w, mi_y, mi_x, _MAX_MSG_LEN);

    MessageHistoryBox _msg_hstr(mh_h, mh_w, mh_y, mh_x,
                                _MAX_HISTORY_LEN, _MAX_MSG_LEN);

    bool exit = false;

    while (1) {
        refresh();
        _msg_box.refresh();
        _msg_hstr.refresh();
        _msg_in.refresh();

        char* msg = _msg_in.input();
        _msg_hstr.add_msg(msg);
        exit = !strncmp(msg, "exit", _MAX_MSG_LEN);

        if (exit) {
            return SC_EXIT;
        }
    }
}

#endif  // SRC_1_SCREEN_GAME_H_
