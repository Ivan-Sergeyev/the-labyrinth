#ifndef SRC_1_SCREEN_GAME_H_
#define SRC_1_SCREEN_GAME_H_

#include <string.h>
#include <stdio.h>
#include <ncurses.h>


#include "screens.h"
#include "message_windows.h"

#include "gamestate.h"
#include "player.h"


player_move_t parse_input(char *str, int len) {
    PLAYER_ACTIONS action = ACT_NONE;
    DIRECTIONS direction = DIR_NONE;

    char *word1 = new char[len];
    char *word2 = new char[len];
    sscanf(str, "%s %s", word1, word2);

    for (int i = 0; i < ACT_NUM_ACTIONS; ++i) {
        if (!strcmp(player_actions_strings[i], word1)) {
            action = (PLAYER_ACTIONS)i;
            break;
        }
    }

    for (int i = 0; i < DIR_NUM_DIRECTIONS; ++i) {
        if (!strcmp(directions_strings[i], word2)) {
            direction = (DIRECTIONS)i;
            break;
        }
    }

    delete[] word1;
    delete[] word2;

    return player_move_t(action, direction);
}


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
    Gamestate gamestate;

    // todo :
    // gamestate.init
    // <create player list>
    // gamestate.set_players
    // player_id = gamestate.get_player_id

    int player_id = 0;
    player_move_t p_move;
    OUTCOMES outcome;

    while (1) {
        refresh();
        _msg_box.refresh();
        _msg_hstr.refresh();
        _msg_in.refresh();

        char* msg = _msg_in.input();
        _msg_hstr.add_msg(msg);
        _msg_hstr.refresh();

        p_move = parse_input(msg, _MAX_MSG_LEN);
        outcome = gamestate.attempt_move(player_id, p_move);
        _msg_hstr.add_msg(outcomes_strings[outcome]);
        _msg_hstr.refresh();

        if (!strncmp(msg, "exit", _MAX_MSG_LEN)) {
            return SC_EXIT;
        }
    }
}

#endif  // SRC_1_SCREEN_GAME_H_
