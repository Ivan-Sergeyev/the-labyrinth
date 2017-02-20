#ifndef SRC_MAP_TILE_H_
#define SRC_MAP_TILE_H_

#include <vector>

using std::vector;


// todo : properly share directions with player.h
#ifndef DEF_DIRECTIONS_
#define DEF_DIRECTIONS_

enum DIRECTIONS {
    DIR_NONE = -1, DIR_LEFT, DIR_UP, DIR_DOWN, DIR_RIHGT, DIR_NUM_DIRECTIONS
};

#endif  // DEF_DIRECTIONS_

enum WALL_TYPES {
    WT_UNDEFINED = -1,
    WT_DESTRUCTIBLE, WT_INDESTRUCTIBLE, WT_MONOLYTH
};


class Wall{
 private:
    DIRECTIONS _direction;
    WALL_TYPES _type;
    bool _enabled;

    void _clear() {
        _direction = DIR_NONE;
        _type = WT_UNDEFINED;
        _enabled = 0;
    }

 public:
    Wall() {
        _clear();
    }

    Wall(DIRECTIONS dir, WALL_TYPES type, bool enabled = 1) :
        _direction(dir), _type(type), _enabled(enabled)
        {}

    Wall(const Wall &other) :
        _direction(other.get_direction()),
        _type(other.get_type()),
        _enabled(other.get_enabled())
        {}

    ~Wall() {
        _clear();
    }

    DIRECTIONS get_direction() const {
        return _direction;
    }

    WALL_TYPES get_type() const {
        return _type;
    }

    bool get_enabled() const {
        return _enabled;
    }

    bool exists() const {
        return _direction != DIR_NONE && _type != WT_UNDEFINED && _enabled;
    }

    bool has_direction(DIRECTIONS direction) const {
        return _direction == direction;
    }

    bool collides(DIRECTIONS direction) const {
        return exists() && has_direction(direction);
    }

    bool destroy() {
        if (!exists()) {
            return 0;
        }
        _enabled = 0;
        return 1;
    }
};


enum MAP_TILE_TYPES {
    MTT_UNDEFINED = -1,
    MTT_EMPTY, MTT_HOLE,
    MTT_RIVER, MTT_RIVER_SOURCE, MTT_RIVER_MOUTH,
    MTT_HOSPITAL, MTT_ARMORY, MTT_EXIT
};


class MapTile {
 private:
    MAP_TILE_TYPES _type;
    vector <Wall> walls;

    vector <Wall>::const_iterator find_wall(DIRECTIONS direction) const {
        vector <Wall>::const_iterator it;
        for (it = walls.begin(); it < walls.end(); ++it) {
            if (it->collides(direction)) {
                return it;
            }
        }
        return walls.end();
    }

    vector <Wall>::iterator find_wall(DIRECTIONS direction) {
        vector <Wall>::iterator it;
        for (it = walls.begin(); it < walls.end(); ++it) {
            if (it->collides(direction)) {
                return it;
            }
        }
        return walls.end();
    }

 public:
    MapTile() : _type(MTT_UNDEFINED) {}

    explicit MapTile(MAP_TILE_TYPES type) : _type(type) {}

    ~MapTile() {
        walls.clear();
        vector <Wall>().swap(walls);
    }

    MAP_TILE_TYPES get_type() const {
        return _type;
    }

    bool has_wall(DIRECTIONS direction) const {
        return find_wall(direction) != walls.end();
    }

    bool add_wall(Wall wall) {
        if (!has_wall(wall.get_direction())) {
            walls.push_back(wall);
            return 1;
        }
        return 0;
    }

    bool destroy_wall_in_direction(DIRECTIONS direction) {
        vector <Wall>::iterator it = find_wall(direction);
        if (it == walls.end()) {
            return 0;
        }
        it->destroy();
        return 1;
    }
};

#endif  // SRC_MAP_TILE_H_
