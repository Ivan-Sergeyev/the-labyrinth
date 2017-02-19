#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "treasure.h"


// enum TILES {};  // todo: see wiki page on rules, see stab in mechanics.h


class Map {
 private:
    int _x_size, _y_size;
    int **_tiles;

    int _num_treasures;
    Treasure *_treasures;

    // todo : add other fields, e.g. exits

 public:
    Map() : _x_size(0), _y_size(0), _tiles(0) {}

    Map(int x_size, int y_size) : _x_size(x_size), _y_size(y_size) {
        // todo : empty map constructor
    }

    void generate(int x_size, int y_size) {
        // todo : add other parameters -- number of special tiles of each type,
        //        number of treasures, etc.
    }

    char* save() {
        // todo : save to string
    }

    void load(char* map_save) {
        // todo : load from string
    }

    void draw() {
        // todo : draw map
        // todo : different draw methods: parts of map, text only, etc
    }
};

#endif  // SRC_MAP_H_
