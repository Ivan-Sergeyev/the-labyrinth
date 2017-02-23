#include <fstream>
#include <memory.h>
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

void GameMap::_clear_num_tiles() {
    memset(_num_tiles, 0, MTT_NUMBER);
}

int GameMap::_load_tiles(std::ifstream &fin) {
    std::string line;
    MAP_TILE_TYPE type;
    MapWall wall_here, wall_there;

    fin >> _x_size >> _y_size;

    for (int x = 0; x < 2 * _x_size - 1; ++x) {
        std::getline(fin, line);
        if (line.length() != (unsigned int) _y_size) {
            return 3;
        }

        if (x % 2 == 1) {
            // tiles
            for (int y = 0; y < 2 * _y_size - 1; y += 2) {
                type = get_tile_type_by_symbol(line[y]);
                ++_num_tiles[type];
                if (type == MTT_UNDEFINED) {
                    return 3;
                }
                _tiles[x][y].set_type(type);
            }

            // vertical walls and horizontal directions
            for (int y = 1; y < 2 * _y_size - 1; y += 2) {
                switch (line[y]) {
                case '|':
                    wall_here = MapWall(DIR_RIGHT, WT_DESTRUCTIBLE);
                    wall_there = MapWall(DIR_LEFT, WT_DESTRUCTIBLE);
                    _tiles[x / 2][y / 2].add_wall(wall_here);
                    _tiles[x / 2 + 1][y / 2].add_wall(wall_there);
                    break;
                case '>':
                    _tiles[x / 2][y / 2].set_next(&(_tiles[x / 2 + 1][y / 2]));
                    break;
                case '<':
                    _tiles[x / 2 + 1][y / 2].set_next(&(_tiles[x / 2][y / 2]));
                    break;
                case ' ':
                    break;
                default:
                    return 3;
                }
            }
        } else {
            // horizontal walls and vertical directions
            for (int y = 0; y < 2 * _y_size - 1; y += 2) {
                switch (line[y]) {
                case '-':
                    wall_here = MapWall(DIR_DOWN, WT_DESTRUCTIBLE);
                    wall_there = MapWall(DIR_UP, WT_DESTRUCTIBLE);
                    _tiles[x / 2][y / 2].add_wall(wall_here);
                    _tiles[x / 2][y / 2 + 1].add_wall(wall_there);
                    break;
                case 'V':
                    _tiles[x / 2][y / 2].set_next(&(_tiles[x / 2][y / 2 + 1]));
                    break;
                case '^':
                    _tiles[x / 2][y / 2 + 1].set_next(&(_tiles[x / 2][y / 2]));
                    break;
                case ' ':
                    break;
                default:
                    return 3;
                }
            }
        }
    }
    return 0;
}

int GameMap::_load_exits(std::ifstream &fin) {
    int num_exits;
    int x, y;
    char d;
    MapTile *tile;

    fin >> num_exits;
    if (num_exits != _num_tiles[MTT_EXIT]) {
        return 3;
    }

    for (int i = 0; i < num_exits; ++i) {
        fin >> x >> y >> d;
        tile = &(_tiles[x - 1][y - 1]);
        if (tile->get_type() != MTT_EXIT) {
            return 3;
        }
        tile->add_wall(MapWall(get_direction_by_symbol(d), WT_EXIT));
    }
    return 0;
}

int GameMap::_load_holes(std::ifstream &fin) {
    int num_holes, num_cycles, len_cycle;
    int x, y;
    MapTile *first_tile;
    MapTile *prev_tile, *cur_tile;

    fin >> num_holes >> num_cycles;
    if (num_holes != _num_tiles[MTT_HOLE]) {
        return 3;
    }

    for (int i = 0; i < num_cycles; ++i) {
        fin >> len_cycle;

        fin >> x >> y;
        first_tile = &(_tiles[x - 1][y - 1]);
        if (first_tile->get_type() != MTT_HOLE) {
            return 3;
        }

        cur_tile = first_tile;
        for (int h = 0; h < len_cycle; ++h) {
            prev_tile = cur_tile;

            fin >> x >> y;
            cur_tile = &(_tiles[x - 1][y - 1]);
            if (cur_tile->get_type() != MTT_HOLE) {
                return 3;
            }
            prev_tile->set_next(cur_tile);
        }
        cur_tile->set_next(first_tile);
    }
    return 0;
}

void GameMap::_save_tiles(std::ofstream &fout) {
    MapTile *tile, *next_tile;
    int offset;

    fout << _x_size << ' ' << _y_size << '\n';

    for (int x = 0; x < _x_size; ++x) {
        for (int y = 0; y < _y_size; ++y) {
            tile = &(_tiles[x][y]);
            fout << MTT_SYMBOL[tile->get_type()];

            if (tile->get_type() == MTT_RIVER) {
                next_tile = tile->get_next();
                offset = (next_tile - tile) / sizeof(MapTile);

                if (offset == 1) {
                    fout << DIRECTION_SYMBOL[DIR_RIGHT];
                } else if (offset == -1) {
                    fout << DIRECTION_SYMBOL[DIR_LEFT];
                }
            }
        }

        fout << '\n';

        if (x == _x_size - 1) {
            continue;
        }

        for (int y = 0; y < _y_size - 1; ++y) {
            tile = &(_tiles[x][y]);
        }
    }

    fout << '\n';
}

void GameMap::_save_exits(std::ofstream &fout) {
    ;
}

void GameMap::_save_holes(std::ofstream &fout) {
    ;
}

GameMap::GameMap() :
    _x_size(0), _y_size(0), _tiles(nullptr) {
    _clear_num_tiles();
}

GameMap::~GameMap() {
    _deallocate();
}

void GameMap::init(int x_size, int y_size) {
    _allocate(x_size, y_size);
    _clear_num_tiles();
}

void GameMap::clear() {
    if (_tiles) {
        for (int x = 0; x < _x_size; ++x) {
            for (int y = 0; y < _y_size; ++y) {
                _tiles[x][y].clear();
            }
        }
    }
    _clear_num_tiles();
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

    int subroutine_ret;
    int version;

    try {
        fin >> version;
        if (version != 1) {
            return 2;
        }

        subroutine_ret = _load_tiles(fin);
        if (subroutine_ret) {
            return subroutine_ret;
        }

        subroutine_ret = _load_exits(fin);
        if (subroutine_ret) {
            return subroutine_ret;
        }

        subroutine_ret = _load_holes(fin);
        if (subroutine_ret) {
            return subroutine_ret;
        }
    } catch (std::ios_base::failure &fb) {
        // todo: deliver exception message from fb.what()
        return 3;
    }

    fin.close();
    return 0;
}

int GameMap::save(const char *filename) const {
    // todo : implement
    if (!is_initialized()) {
        return 2;
    }

    std::ofstream fout(filename);
    if (!fout) {
        return 1;
    }

    int version = 1;
    fout << version << '\n';

    _save_tiles(fout);
    _save_exits(fout);
    _save_holes(fout);

    return 0;  // failed
}

bool GameMap::can_move(int from_x, int from_y, DIRECTION dir) const {
    return !_tiles[from_x][from_y].has_wall(dir);
}
