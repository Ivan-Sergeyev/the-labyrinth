#ifndef SRC_GRAPHICS_HEADERS_1_SCREEN_LOBBY_H_
#define SRC_GRAPHICS_HEADERS_1_SCREEN_LOBBY_H_

#include "../../mechanics/headers/gamestate.h"


SCREEN_ID lobby(Gamestate *gamestate) {
    gamestate = new Gamestate();
    // todo :
    // gamestate.init
    // <create player list>
    // gamestate.set_players
    // gamestate.init();

    return SCR_GAME;
}

#endif  // SRC_GRAPHICS_HEADERS_1_SCREEN_LOBBY_H_
