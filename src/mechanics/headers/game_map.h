#ifndef SRC_MECHANICS_HEADERS_GAME_MAP_H_
#define SRC_MECHANICS_HEADERS_GAME_MAP_H_


#include "map_tile.h"


class GameMap {
 private:
    int _x_size, _y_size;
    MapTile **_tiles;

    void _allocate(int new_x_size, int new_y_size);
    void _deallocate();

 public:
    GameMap();

    ~GameMap();

    void init(int x_size, int y_size);
    void clear();

    bool is_initialized() const;

    bool generate();
    int load(const char *filename);
    int save(const char *filename) const;

    bool can_move(int from_x, int from_y, DIRECTIONS dir) const;
};

#endif  // SRC_MECHANICS_HEADERS_GAME_MAP_H_
