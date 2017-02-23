#ifndef SRC_GRAPHICS_HEADERS_1_SCREEN_HOST_LOBBY_H_
#define SRC_GRAPHICS_HEADERS_1_SCREEN_HOST_LOBBY_H_

#include "../../mechanics/headers/gamestate.h"


SCREEN_ID host_lobby(Gamestate *gamestate) {
    delete gamestate;
    gamestate = new Gamestate();
    gamestate->generate_map(5, 5);
    return SCR_GAME;
}

#endif  // SRC_GRAPHICS_HEADERS_1_SCREEN_HOST_LOBBY_H_
