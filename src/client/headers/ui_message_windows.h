#ifndef SRC_CLIENT_HEADERS_MESSAGE_WINDOWS_H_
#define SRC_CLIENT_HEADERS_MESSAGE_WINDOWS_H_

#include <string.h>

#include <string>
#include <vector>

#include "ui_box_window.h"

using std::string;
using std::vector;


class MessageHistoryBox : public BoxWindow {
 private:
    int _history_length;
    vector<string> _history;

 public:
    MessageHistoryBox(int h, int w, int y, int x, int history_length) :
        BoxWindow(h, w, y, x),
        _history_length(history_length),
        _history(history_length)
    {}

    ~MessageHistoryBox() {
        _history.resize(0);
        _history_length = 0;
    }

    void redraw() const {
        // todo : scroll history with pgup/pgdn
        int history_size = _history.size();
        int msg_idx;
        int pos_col = 2;
        int pos_row;

        for (int i = 0; i < _history_length; ++i) {
            pos_row = _history_length - i;
            msg_idx = history_size - 1 - i;
            mvwprintw(_window, pos_row, pos_col, _history[msg_idx].c_str());
        }
    }

    void add_msg(const string msg) {
        _history.push_back(msg);
    }
};


class MessageInputBox : public BoxWindow {
 private:
    int _max_message_length;

 public:
    MessageInputBox(int h, int w, int y, int x, int max_message_length) :
        BoxWindow(h, w, y, x),
        _max_message_length(max_message_length)
    {}

    ~MessageInputBox() {
        _max_message_length = 0;
    }

    int get_max_message_length() const {
        return _max_message_length;
    }

    void redraw() const {
        mvwprintw(_window, 1, 1, "> ");
    }

    string input() {
        char *input_cstring = new char [_max_message_length];
        wgetnstr(_window, input_cstring, _max_message_length - 1);
        string input_string(input_cstring);
        delete [] input_cstring;
        return input_string;
    }
};

#endif  // SRC_CLIENT_HEADERS_MESSAGE_WINDOWS_H_
