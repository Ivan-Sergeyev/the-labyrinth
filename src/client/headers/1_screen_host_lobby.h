#ifndef SRC_CLIENT_HEADERS_1_SCREEN_HOST_LOBBY_H_
#define SRC_CLIENT_HEADERS_1_SCREEN_HOST_LOBBY_H_

#include <iostream>

#include "general_screen.h"
#include "2_screen_game.h"


class ScreenHostLobby : public GeneralScreen {
 public:
    ScreenHostLobby() {}
    ~ScreenHostLobby() {}

    GeneralScreen* loop(Gamestate **gamestate) {
        // todo : change argument from gamestate to host sockfd

        // todo : fork
        // parent is client, child is host
        // create socket, commence communication

        // note : transfer gamestate to class Host
        std::cerr << "ok start lobby\n";
        *gamestate = new Gamestate(1);
        std::cerr << "ok new gamestate\n";
        int ret = (*gamestate)->generate_map(5, 5);
        std::cerr << "ok generate map\n";

        if (!ret) {
            // std::cerr << "failed to generate map\n";
            return nullptr;
        } else {
            // std::cerr << "map generation successful\n";
        }

        std::cerr << "ok\n";
        GeneralScreen *next_screen = new ScreenGame();
        std::cerr << "ok\n";
        return next_screen;
    }
};

#endif  // SRC_CLIENT_HEADERS_1_SCREEN_HOST_LOBBY_H_
