#ifndef SRC_GAMESTATE_H_
#define SRC_GAMESTATE_H_

#include "map_tile.h"
#include "player.h"


class Gamestate {
 private:
    int _x_size, _y_size;

    int _num_players;
    int _num_treasures;

    MapTile **_tiles;
    Treasure *_treasures;

    Player *_players;

 public:
    Gamestate() :
        _x_size(0), _y_size(0), _tiles(0),
        _num_treasures(0), _treasures(nullptr),
        _num_players(0), _players(nullptr)
        {}

    ~Gamestate() {
        if (_tiles) {
            for(int i = 0; i < _x_size; ++i) {
                delete[] _tiles[i];
            }
            delete[] _tiles;
        }

        delete[] _treasures;
        delete[] _players;
    }

    void init(int x_size, int y_size, int num_treasures,
              int num_players, const Player *players) {
        _x_size = x_size;
        _y_size = y_size;
        _tiles = new MapTile*[_x_size];
        for(int i = 0; i < _x_size; ++i) {
            _tiles[i] = new MapTile[_y_size];
        }

        _num_treasures = num_treasures;
        _treasures = new Treasure[num_treasures];

        _num_players = num_players;
        _players = new Player[num_players];
    }

    void generate_map() {
        // todo : add other parameters -- number of special tiles of each type,
        //        number of treasures, etc.
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
