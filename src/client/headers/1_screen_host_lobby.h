#ifndef SRC_CLIENT_HEADERS_1_SCREEN_HOST_LOBBY_H_
#define SRC_CLIENT_HEADERS_1_SCREEN_HOST_LOBBY_H_

#include <iostream>

#include "../../host/headers/gamestate.h"


SCREEN_ID host_lobby(Gamestate **gamestate) {
    // todo : change argument from gamestate to host sockfd

    // todo : fork
    // parent is client, child is host
    // create socket, commence communication

    // note : transfer gamestate creation to class Host
    delete *gamestate;
    *gamestate = new Gamestate(1);

    int ret = (*gamestate)->generate_map(5, 5);
    if (!ret) {
        // std::cerr << "failed to generate map\n";
        return SCR_EXIT;
    } else {
        // std::cerr << "map generation successful\n";
    }

    //
    return SCR_GAME;
}

#endif  // SRC_CLIENT_HEADERS_1_SCREEN_HOST_LOBBY_H_
