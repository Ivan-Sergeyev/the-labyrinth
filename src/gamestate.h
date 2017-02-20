#ifndef SRC_GAMESTATE_H_
#define SRC_GAMESTATE_H_

#include "map_tile.h"
#include "player.h"


class Gamestate {
 private:
    int _x_size, _y_size;
    MapTile **_tiles;

    int _num_treasures;
    Treasure *_treasures;

    int _num_players;
    Player *_players;

    // todo : add other fields, e.g. list of exits

 public:
    Gamestate() :
        _x_size(0), _y_size(0), _tiles(0),
        _num_treasures(0), _treasures(0),
        _num_players(0), _players(0)
        {}

    void generate_map(int x_size, int y_size) {
        // todo : add other parameters -- number of special tiles of each type,
        //        number of treasures, etc.
    }

    void draw_ncurses() {
        // todo : draw map
        // todo : different draw methods: e.g. messages only
    }

    void attempt_move() {
        // todo
    }

    const Player* get_player(int idx) const {
        if (idx >= 0 && idx < _num_players) {
            return &(_players[idx]);
        }
        return 0;
    }

// todo : save
// todo : load
};

#endif  // SRC_GAMESTATE_H_
