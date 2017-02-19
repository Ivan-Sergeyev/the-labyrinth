#ifndef SRC_GAMESTATE_H_
#define SRC_GAMESTATE_H_

#include "map.h"
#include "player.h"


class Gamestate {
 private:
    Map *_map;
    Player *_players;

 public:
    Gamestate() {}

    void save() {
        // todo : save game
    }

    void load() {
        // todo : load game
    }
};

#endif  // SRC_GAMESTATE_H_
