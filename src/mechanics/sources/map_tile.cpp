#include "../headers/map_tile.h"


MapTile::MapTile() :
    _type(MTT_UNDEFINED), _next(nullptr) {}

MapTile::MapTile(MAP_TILE_TYPES type) :
    _type(type), _next(nullptr) {}

MAP_TILE_TYPES MapTile::get_type() const {
    return _type;
}

MapTile* MapTile::get_next() const {
    return _next;
}

void MapTile::set_next(MapTile *next) {
    _next = next;
}

bool MapTile::has_wall(DIRECTIONS dir) const {
    return dir != DIR_NONE && _walls[dir].exists();
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
