#include "map_wall.h"


void MapWall::_clear() {
    _direction = DIR_NONE;
    _type = WT_UNDEFINED;
    _enabled = false;
}

MapWall::MapWall() {
    _clear();
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
    _clear();
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

bool MapWall::has_direction(DIRECTIONS direction) const {
    return _direction == direction;
}

bool MapWall::collides(DIRECTIONS direction) const {
    return exists() && has_direction(direction);
}

bool MapWall::destroy() {
    if (!exists()) {
        return false;
    }
    _enabled = false;
    return true;
}
