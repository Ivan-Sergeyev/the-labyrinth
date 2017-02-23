#ifndef SRC_GRAPHICS_HEADERS_2_SCREEN_GAME_H_
#define SRC_GRAPHICS_HEADERS_2_SCREEN_GAME_H_

#include <cstring>
#include <stdio.h>


#include "screens.h"
#include "message_windows.h"

#include "../../mechanics/headers/gamestate.h"


const char PLAYER_ACTION_STRING[ACT_NUMBER][6] = {
    "skip", "move", "knife", "shoot", "bomb"
};


player_move_t parse_input(char *str, int len) {
    PLAYER_ACTION action = ACT_NONE;
    DIRECTION direction = DIR_NONE;

    char *word1 = new char[len];
    char *word2 = new char[len];
    sscanf(str, "%s %s", word1, word2);

    for (int i = 0; i < ACT_NUMBER; ++i) {
        if (!strcmp(PLAYER_ACTION_STRING[i], word1)) {
            action = (PLAYER_ACTION) i;
            break;
        }
    }

    for (int i = 0; i < DIR_NUMBER; ++i) {
        if (!strcmp(DIRECTION_STRING[i], word2)) {
            direction = (DIRECTION) i;
            break;
        }
    }

    delete[] word1;
    delete[] word2;

    return player_move_t(action, direction);
}


SCREEN_ID game(Gamestate **gamestate) {
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

    // player_id = gamestate.get_player_id
    // todo : add interface for talking to gamestate
    int player_id = 0;
    player_move_t p_move;
    OUTCOME outcome;

    while (1) {
        refresh();
        _msg_box.refresh();
        _msg_hstr.refresh();
        _msg_in.refresh();

        char* msg = _msg_in.input();
        _msg_hstr.add_msg(msg);
        _msg_hstr.refresh();

        p_move = parse_input(msg, _MAX_MSG_LEN);
        outcome = (*gamestate)->request_move(player_id, p_move);
        _msg_hstr.add_msg(OUTCOME_STRING[outcome]);
        _msg_hstr.refresh();

        if (!strncmp(msg, "exit", _MAX_MSG_LEN)) {
            delete gamestate;
            return SCR_EXIT;
        }
    }
}

#endif  // SRC_GRAPHICS_HEADERS_2_SCREEN_GAME_H_
