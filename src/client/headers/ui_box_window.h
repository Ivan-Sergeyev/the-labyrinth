#ifndef SRC_CLIENT_HEADERS_UI_BOX_WINDOW_H_
#define SRC_CLIENT_HEADERS_UI_BOX_WINDOW_H_

#include <ncurses.h>


class BoxWindow {
 private:
    int _h, _w, _y, _x;

 protected:
    WINDOW *_window;

 public:
    BoxWindow(int h, int w, int y, int x) :
            _h(h), _w(w), _y(y), _x(x) {
        _window = newwin(_h, _w, _y, _x);
    }

    ~BoxWindow() {
        delwin(_window);
    }

    virtual void refresh() const {
        if (!_window) {
            return;
        }
        wclear(_window);
        box(_window, 0, 0);
        redraw();
        wrefresh(_window);
    }

    virtual void redraw() const {}
};

#endif  // SRC_CLIENT_HEADERS_UI_BOX_WINDOW_H_
