#include <iostream>
#include "../headers/map_tile.h"


MAP_TILE_TYPE get_tile_type_by_symbol(char c) {
    for (int t = 0; t < MTT_NUMBER; ++t) {
        if (c == MTT_SYMBOL[t]) {
            return (MAP_TILE_TYPE) t;
        }
    }
    return MTT_UNDEFINED;
}

MapTile::MapTile() {
    clear();
}

MapTile::MapTile(MAP_TILE_TYPE type) :
    _type(type), _next(nullptr) {}

void MapTile::clear() {
    _type = MTT_UNDEFINED;
    _next = nullptr;
    for (int d = 0; d < DIR_NUMBER; ++d) {
        _walls[d].clear();
    }
}

MAP_TILE_TYPE MapTile::get_type() const {
    return _type;
}

MapTile* MapTile::get_next() const {
    return _next;
}

bool MapTile::has_wall(DIRECTION dir) const {
    std::cerr << "in has wall: ";
    for (int d = 0; d < DIR_NUMBER; ++d) {
        std::cerr << _walls[d].exists() << ' ';
    }
    std::cerr << '\n';
    return dir != DIR_NONE && _walls[dir].exists();
}

void MapTile::set_type(MAP_TILE_TYPE type) {
    _type = type;
}

void MapTile::set_next(MapTile *next) {
    _next = next;
}

bool MapTile::add_wall(MapWall wall) {
    DIRECTION dir = wall.get_direction();
    std::cerr << "adding wall in direction " << dir << '\n';
    if (!has_wall(dir)) {
        _walls[dir] = wall;
        return true;
    }
    return false;
}

bool MapTile::destroy_wall_in_direction(DIRECTION dir) {
    return _walls[dir].destroy();
}
