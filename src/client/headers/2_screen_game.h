#ifndef SRC_CLIENT_HEADERS_2_SCREEN_GAME_H_
#define SRC_CLIENT_HEADERS_2_SCREEN_GAME_H_

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "general_screen.h"
#include "ui_message_windows.h"
#include "../../host/headers/host.h"

using std::cerr;

#define MAXDATASIZE 100  // max number of bytes we can get at once


class ScreenGame : public GeneralScreen {
 private:
    int _host_socket_fd;
    int _player_id;

    string _get_outcome(const string &msg) {
        cerr << "client : send message \"" << msg << "\" to host\n";
        int numbytes = send(_host_socket_fd, msg.c_str(), MAXDATASIZE - 1, 0);
        if (numbytes == -1) {
            perror("client : send");
        }

        char *buf = new char[MAXDATASIZE];
        numbytes = recv(_host_socket_fd, buf, MAXDATASIZE - 1, 0);
        if (numbytes == -1) {
            perror("client : recv");
            const char *str_outcome = OUTCOME_STRING[OUT_INVALID];
            numbytes = strlen(str_outcome);
            strncpy(buf, str_outcome, numbytes);
        }
        buf[numbytes] = '\0';

        string response(buf);
        delete [] buf;
        return response;
    }

 public:
    ScreenGame() {}
    ~ScreenGame() {}

    void set_host_socket(int socket_fd) {
        _host_socket_fd = socket_fd;
    }

    void set_player_id(int player_id) {
        _player_id = player_id;
    }

    GeneralScreen* loop() {
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

        MessageHistoryBox _msg_hstr(mh_h, mh_w, mh_y, mh_x, _MAX_HISTORY_LEN);

        player_move_t p_move;
        string msg, buf;

        while (1) {
            refresh();
            _msg_box.refresh();
            _msg_hstr.refresh();
            _msg_in.refresh();

            msg = _msg_in.input();
            if (msg.empty()) {
                continue;
            }

            _msg_hstr.add_msg(msg);
            _msg_hstr.refresh();

            buf = _get_outcome(msg);
            _msg_hstr.add_msg(buf);
            _msg_hstr.refresh();

            if (msg == "exit") {
                cerr << "client : exit\n";
                clear();
                return nullptr;
            }
        }
    }
};

#endif  // SRC_CLIENT_HEADERS_2_SCREEN_GAME_H_
