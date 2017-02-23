#ifndef SRC_GRAPHICS_HEADERS_MESSAGE_WINDOWS_H_
#define SRC_GRAPHICS_HEADERS_MESSAGE_WINDOWS_H_

#include "string.h"

#include "box_window.h"


class MessageHistoryBox : public BoxWindow {
 private:
    int _history_length;
    int _message_max_length;
    int _oldest_idx;
    char **_history;

 public:
    MessageHistoryBox(int h, int w, int y, int x, int hstr_len, int msg_len) :
            BoxWindow(h, w, y, x),
            _history_length(hstr_len),
            _message_max_length(msg_len),
            _oldest_idx(0),
            _history (new char*[_history_length]) {
        for (int i = 0; i < _history_length; ++i) {
            _history[i] = new char[_message_max_length];
            memset(_history[i], 0, _message_max_length);
        }
    }

    ~MessageHistoryBox() {
        for (int i = 0; i < _history_length; ++i) {
            delete[] _history[i];
            _history[i] = nullptr;
        }
        delete[] _history;
        _history = nullptr;

        _history_length = 0;
        _message_max_length = 0;
        _oldest_idx = 0;
    }

    void redraw() const {
        for (int i = 0; i < _history_length; ++i) {
            int history_out_y = i + _history_length - _oldest_idx;
            history_out_y = history_out_y % _history_length;
            mvwprintw(_window, 1 + history_out_y, 2, _history[i]);
        }
    }

    void add_msg(const char *msg) {
        strncpy(_history[_oldest_idx], msg, _message_max_length);
        _oldest_idx = (_oldest_idx + 1) % _history_length;
    }
};


class MessageInputBox : public BoxWindow {
 private:
    int _message_max_length;
    char *_input_string;

 public:
    MessageInputBox(int h, int w, int y, int x, int msg_len) :
            BoxWindow(h, w, y, x),
            _message_max_length(msg_len),
            _input_string(new char[_message_max_length]) {
        memset(_input_string, 0, _message_max_length);
    }

    ~MessageInputBox() {
        delete[] _input_string;
        _input_string = nullptr;
        _message_max_length = 0;
    }

    int get_message_max_length() const {
        return _message_max_length;
    }

    void redraw() const {
        mvwprintw(_window, 1, 1, "> ");
    }

    char* input() {
        wgetnstr(_window, _input_string, _message_max_length - 1);
        return _input_string;
    }
};

#endif  // SRC_GRAPHICS_HEADERS_MESSAGE_WINDOWS_H_
