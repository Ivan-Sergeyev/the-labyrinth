#include <fstream>
#include <string>

#include "../headers/game_map.h"


void GameMap::_allocate(int new_x_size, int new_y_size) {
    _deallocate();
    _x_size = new_x_size;
    _y_size = new_y_size;

    if (!_x_size || !_y_size) {
        return;
    }
    _tiles = new MapTile*[_x_size];
    for (int x = 0; x < _x_size; ++x) {
        _tiles[x] = new MapTile[_y_size];
    }
}

void GameMap::_deallocate() {
    if (_tiles) {
        for (int x = 0; x < _x_size; ++x) {
            delete[] _tiles[x];
        }
        delete[] _tiles;
        _tiles = nullptr;
    }
}

GameMap::GameMap() :
    _x_size(0), _y_size(0), _tiles(nullptr) {}

GameMap::~GameMap() {
    _deallocate();
}

void GameMap::init(int x_size, int y_size) {
    _allocate(x_size, y_size);
}

void GameMap::clear() {
    for (int x = 0; x < _x_size; ++x) {
        for (int y = 0; y < _y_size; ++y) {
            _tiles[x][y].clear();
        }
    }
}

bool GameMap::is_initialized() const {
    return _x_size != 0 && _y_size != 0 && _tiles != nullptr;
}

bool GameMap::generate() {
    // return true;  // success
    // return false;  // failure

    // todo : implement real generation
    // todo : add other parameters -- number of special tiles of each type,
    //        number of treasures, etc.

    int load_result = load("test/test.maze");
    return load_result == 0;
}

int GameMap::load(const char *filename) {
    // returns
    // 0 = ok
    // 1 = file missing
    // 2 = version not recognized
    // 3 = format error

    std::ifstream fin(filename);
    if (!fin) {
        return 1;
    }

    fin.exceptions(std::ios::failbit);

    try {
        int version;
        fin >> version;
        if (version != 1) {
            return 2;
        }

        int _num_exits = 0;
        int _num_holes = 0;
        fin >> _x_size >> _y_size;

        for (int x = 0; x < 2 * _x_size - 1; ++x) {
            std::string line;
            std::getline(fin, line);
            if (line.length() != (unsigned int) _y_size) {
                return 3;
            }

            if (x % 2 == 1) {
                for (int y = 0; y < 2 * _y_size - 1; y += 2) {
                    MAP_TILE_TYPES type = get_tile_type_by_symbol(line[y]);
                    if (type == MTT_UNDEFINED) {
                        return 3;
                    }
                    _tiles[x][y].set_type(type);
                }
                for (int y = 1; y < 2 * _y_size - 1; y += 2) {
                    switch (line[y]) {
                    case '|':
                        _tiles[x / 2][y / 2].add_wall(MapWall(DIR_DOWN, WT_DESTRUCTIBLE));
                        _tiles[x / 2 + 1][y / 2].add_wall(MapWall(DIR_UP, WT_DESTRUCTIBLE));
                        break;
                    case '>':
                        _tiles[x / 2][y / 2].set_next(&_tiles[x / 2 + 1][y / 2]);
                        break;
                    case '<':
                        _tiles[x / 2 + 1][y / 2].set_next(&_tiles[x / 2][y / 2]);
                        break;
                    case ' ':
                        break;
                    default:
                        return 3;
                    }
                }
            } else {
                for (int y = 0; y < 2 * _y_size - 1; y += 2) {
                    switch (line[y]) {
                    case '-':
                        _tiles[x / 2][y / 2].add_wall(MapWall(DIR_DOWN, WT_DESTRUCTIBLE));
                        _tiles[x / 2][y / 2 + 1].add_wall(MapWall(DIR_UP, WT_DESTRUCTIBLE));
                        break;
                    case 'V':
                        _tiles[x / 2][y / 2].set_next(&_tiles[x / 2][y / 2 + 1]);
                        break;
                    case '^':
                        _tiles[x / 2][y / 2 + 1].set_next(&_tiles[x / 2][y / 2]);
                        break;
                    case ' ':
                        break;
                    default:
                        return 3;
                    }
                }
            }
        }

        int num_exits;
        fin >> num_exits;
        if (num_exits != _num_exits) {
            return 3;
        }
        // todo : add exits

        int num_holes;
        fin >> num_holes;
        if (num_holes != _num_holes) {
            return 3;
        }
        // todo : add holes
    } catch (std::ios_base::failure &fb) {
        // todo: deliver exception message from fb.what()
        return 3;
    }

    fin.close();
    return 0;
}

int GameMap::save(const char *filename) const {
    // todo : implement
    return 0;  // failed
}

bool GameMap::can_move(int from_x, int from_y, DIRECTION dir) const {
    return !_tiles[from_x][from_y].has_wall(dir);
}
