#ifndef SRC_GAMESTATE_H_
#define SRC_GAMESTATE_H_

#include "map_tile.h"
#include "player.h"


enum PLAYER_ACTIONS {ACT_SKIP = 0, ACT_MOVE, ACT_MELEE, ACT_SHOOT, ACT_BOMB};
enum DIRECTIONS {DIR_NONE = -1, DIR_LEFT, DIR_UP, DIR_DOWN, DIR_RIHGT};
enum OUTCOMES {OUT_SKIP = 0, OUT_PASS, OUT_WALL, OUT_WOUND, OUT_KILL,
               OUT_BOMB_SUCCESS, OUT_BOMB_FAIL};


class Gamestate {
 private:
    int _x_size, _y_size;
    MapTile **_tiles;

    int _num_treasures;
    Treasure *_treasures;

    Player *_players;

    // todo : add other fields, e.g. list of exits

 public:
    Gamestate() : _x_size(0), _y_size(0), _tiles(0) {}

    Gamestate(int x_size, int y_size) : _x_size(x_size), _y_size(y_size) {
        // todo : empty map constructor
    }

    void generate_map(int x_size, int y_size) {
        // todo : add other parameters -- number of special tiles of each type,
        //        number of treasures, etc.
    }

// todo : save
// todo : load

    void draw_ncurses() {
        // todo : draw map
        // todo : different draw methods: e.g. messages only
    }

    void attempt_move() {
        // todo
    }
};

#endif  // SRC_GAMESTATE_H_
