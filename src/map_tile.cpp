#include "map_tile.h"


vector <MapWall>::const_iterator MapTile::find_wall(DIRECTIONS dir) const {
    vector <MapWall>::const_iterator it;
    for (it = walls.begin(); it < walls.end(); ++it) {
        if (it->collides(dir)) {
            return it;
        }
    }
    return walls.end();
}

vector <MapWall>::iterator MapTile::find_wall(DIRECTIONS dir) {
    vector <MapWall>::iterator it;
    for (it = walls.begin(); it < walls.end(); ++it) {
        if (it->collides(dir)) {
            return it;
        }
    }
    return walls.end();
}

MapTile::MapTile() : _type(MTT_UNDEFINED) {}

MapTile::MapTile(MAP_TILE_TYPES type) : _type(type) {}

MapTile::~MapTile() {
    walls.clear();
    vector <MapWall>().swap(walls);
}

MAP_TILE_TYPES MapTile::get_type() const {
    return _type;
}

bool MapTile::has_wall(DIRECTIONS dir) const {
    return find_wall(dir) != walls.end();
}

bool MapTile::add_wall(MapWall wall) {
    if (!has_wall(wall.get_direction())) {
        walls.push_back(wall);
        return true;
    }
    return false;
}

bool MapTile::destroy_wall_in_direction(DIRECTIONS dir) {
    vector <MapWall>::iterator it = find_wall(dir);
    if (it == walls.end()) {
        return false;
    }
    it->destroy();
    return true;
}
