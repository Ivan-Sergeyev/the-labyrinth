#ifndef SRC_GRAPHICS_HEADERS_1_SCREEN_LOBBY_H_
#define SRC_GRAPHICS_HEADERS_1_SCREEN_LOBBY_H_

#include "../../mechanics/headers/gamestate.h"


SCREEN_ID lobby(Gamestate *gamestate) {
    gamestate = new Gamestate();

    int map_size_x = 5, map_size_y = 5;

    return SCR_GAME;
}

#endif  // SRC_GRAPHICS_HEADERS_1_SCREEN_LOBBY_H_
