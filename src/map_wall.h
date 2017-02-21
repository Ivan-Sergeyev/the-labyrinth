#ifndef SRC_MAP_WALL_H_
#define SRC_MAP_WALL_H_

#include "directions.h"

enum MAP_WALL_TYPES {
    WT_UNDEFINED = -1,
    WT_DESTRUCTIBLE, WT_INDESTRUCTIBLE, WT_MONOLYTH
};


class MapWall {
 private:
    DIRECTIONS _direction;
    MAP_WALL_TYPES _type;
    bool _enabled;

    void _clear();

 public:
    MapWall();
    MapWall(DIRECTIONS dir, MAP_WALL_TYPES type, bool enabled = true);
    MapWall(const MapWall &other);

    ~MapWall();

    DIRECTIONS get_direction() const;
    MAP_WALL_TYPES get_type() const;
    bool get_enabled() const;

    bool exists() const;
    bool has_direction(DIRECTIONS direction) const;
    bool collides(DIRECTIONS direction) const;

    bool destroy();
};

#endif  // SRC_MAP_WALL_H_
