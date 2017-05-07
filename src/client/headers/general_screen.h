#ifndef SRC_CLIENT_HEADERS_GENERAL_SCREEN_H_
#define SRC_CLIENT_HEADERS_GENERAL_SCREEN_H_

#include <ncurses.h>

#include "../../host/headers/gamestate.h"


class GeneralScreen {
 public:
    GeneralScreen() {}
    virtual ~GeneralScreen() {}

    // todo : move gamestate to host
    virtual GeneralScreen* loop(Gamestate **gamestate) = 0;
};

#endif  // SRC_CLIENT_HEADERS_GENERAL_SCREEN_H_
