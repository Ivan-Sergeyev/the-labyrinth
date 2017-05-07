#ifndef SRC_CLIENT_HEADERS_APP_H_
#define SRC_CLIENT_HEADERS_APP_H_

#include "general_screen.h"
#include "../../host/headers/gamestate.h"


class App {
 private:
    Gamestate **_gamestate;  // todo : move gamestate to host
    GeneralScreen *_screen_cur;

 public:
    explicit App(GeneralScreen *screen);
    ~App();

    int run();

    // todo : move gamestate to host
    void new_gamestate();
    void delete_gamestate();
};

#endif  // SRC_CLIENT_HEADERS_APP_H_
