#ifndef SRC_GRAPHICS_HEADERS_1_SCREEN_HOST_LOBBY_H_
#define SRC_GRAPHICS_HEADERS_1_SCREEN_HOST_LOBBY_H_

#include <iostream>

#include "../../mechanics/headers/gamestate.h"


SCREEN_ID host_lobby(Gamestate **gamestate) {
    delete *gamestate;
    *gamestate = new Gamestate();

    if ((*gamestate)->generate_map(5, 5)) {
        std::cerr << "failed to generate map\n";
        return SCR_EXIT;
    } else {
        std::cerr << "map generation successful\n";
    }

    return SCR_GAME;
}

#endif  // SRC_GRAPHICS_HEADERS_1_SCREEN_HOST_LOBBY_H_
