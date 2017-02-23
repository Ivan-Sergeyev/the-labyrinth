#include "../headers/map_tile.h"


MapTile::MapTile() {
    clear();
}

MapTile::MapTile(MAP_TILE_TYPES type) :
    _type(type), _next(nullptr) {}

void MapTile::clear() {
    _type = MTT_UNDEFINED;
    _next = nullptr;
    for (int d = 0; d < DIR_NUM_DIRECTIONS; ++d) {
        _walls[d].clear();
    }
}

MAP_TILE_TYPES MapTile::get_type() const {
    return _type;
}

MapTile* MapTile::get_next() const {
    return _next;
}

bool MapTile::has_wall(DIRECTIONS dir) const {
    return dir != DIR_NONE && _walls[dir].exists();
}

void MapTile::set_type(MAP_TILE_TYPES type) {
    _type = type;
}

void MapTile::set_next(MapTile *next) {
    _next = next;
}

bool MapTile::add_wall(MapWall wall) {
    DIRECTIONS dir = wall.get_direction();
    if (!has_wall(dir)) {
        _walls[dir] = wall;
        return true;
    }
    return false;
}

bool MapTile::destroy_wall_in_direction(DIRECTIONS dir) {
    return _walls[dir].destroy();
}
