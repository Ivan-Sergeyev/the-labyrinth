#ifndef SRC_CLIENT_HEADERS_APP_H_
#define SRC_CLIENT_HEADERS_APP_H_


#include "general_screen.h"


class App {
 private:
    GeneralScreen *_screen_cur;

    void _ncurses_init();
    void _ncurses_quit();

 public:
    explicit App(GeneralScreen *screen);
    ~App();

    int run();
};

#endif  // SRC_CLIENT_HEADERS_APP_H_
