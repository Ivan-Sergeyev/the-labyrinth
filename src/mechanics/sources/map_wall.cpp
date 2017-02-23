#include "../headers/map_wall.h"


MapWall::MapWall() {
    clear();
}

MapWall::MapWall(DIRECTIONS dir, MAP_WALL_TYPES type, bool enabled) :
    _direction(dir), _type(type), _enabled(enabled)
    {}

MapWall::MapWall(const MapWall &other) :
    _direction(other.get_direction()),
    _type(other.get_type()),
    _enabled(other.get_enabled())
    {}

MapWall::~MapWall() {
    clear();
}

void MapWall::clear() {
    _direction = DIR_NONE;
    _type = WT_UNDEFINED;
    _enabled = false;
}

DIRECTIONS MapWall::get_direction() const {
    return _direction;
}

MAP_WALL_TYPES MapWall::get_type() const {
    return _type;
}

bool MapWall::get_enabled() const {
    return _enabled;
}

bool MapWall::exists() const {
    return _direction != DIR_NONE && _type != WT_UNDEFINED && _enabled;
}

bool MapWall::has_direction(DIRECTIONS dir) const {
    return _direction == dir;
}

bool MapWall::collides(DIRECTIONS dir) const {
    return exists() && has_direction(dir);
}

bool MapWall::destroy() {
    if (!exists()) {
        return false;
    }
    _enabled = false;
    return true;
}
