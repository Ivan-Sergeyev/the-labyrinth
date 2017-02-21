#include "map_tile.h"


MapTile::MapTile() : _type(MTT_UNDEFINED) {}

MapTile::MapTile(MAP_TILE_TYPES type) : _type(type) {}

MAP_TILE_TYPES MapTile::get_type() const {
    return _type;
}

bool MapTile::has_wall(DIRECTIONS dir) const {
    return dir != DIR_NONE && walls[dir].exists();
}

bool MapTile::add_wall(MapWall wall) {
    DIRECTIONS dir = wall.get_direction();
    if (!has_wall(dir)) {
        walls[dir] = wall;
        return true;
    }
    return false;
}

bool MapTile::destroy_wall_in_direction(DIRECTIONS dir) {
    return walls[dir].destroy();
}
