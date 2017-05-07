#ifndef SRC_CLIENT_HEADERS_GENERAL_SCREEN_H_
#define SRC_CLIENT_HEADERS_GENERAL_SCREEN_H_

#include <ncurses.h>


class GeneralScreen {
 public:
    GeneralScreen() {}
    virtual ~GeneralScreen() {}

    virtual GeneralScreen* loop() = 0;
};

#endif  // SRC_CLIENT_HEADERS_GENERAL_SCREEN_H_
