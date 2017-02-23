#ifndef SRC_MECHANICS_HEADERS_GAME_MAP_H_
#define SRC_MECHANICS_HEADERS_GAME_MAP_H_

#include <fstream>

#include "map_tile.h"


class GameMap {
 private:
    int _x_size, _y_size;
    MapTile **_tiles;

    int _num_tiles[MTT_NUMBER];

    void _allocate(int new_x_size, int new_y_size);
    void _deallocate();

    void _clear_num_tiles();

    int _load_tiles(std::ifstream &fin);
    int _load_exits(std::ifstream &fin);
    int _load_holes(std::ifstream &fin);

    void _save_tiles(std::ofstream &fout) const;
    void _save_exits(std::ofstream &fout) const;
    void _save_holes(std::ofstream &fout) const;

 public:
    GameMap();

    ~GameMap();

    void init(int x_size, int y_size);
    void clear();

    bool is_initialized() const;

    bool generate();
    int load(const char *filename);
    int save(const char *filename) const;

    bool can_move(int from_x, int from_y, DIRECTION dir) const;

    MapWall& get_wall(int x, int y, DIRECTION dir);
};

#endif  // SRC_MECHANICS_HEADERS_GAME_MAP_H_
