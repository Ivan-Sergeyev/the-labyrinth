#ifndef SRC_MECHANICS_HEADERS_MAP_WALL_H_
#define SRC_MECHANICS_HEADERS_MAP_WALL_H_

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

 public:
    MapWall();
    MapWall(DIRECTIONS dir, MAP_WALL_TYPES type, bool enabled = true);
    MapWall(const MapWall &other);

    ~MapWall();

    void clear();

    DIRECTIONS get_direction() const;
    MAP_WALL_TYPES get_type() const;
    bool get_enabled() const;

    bool exists() const;
    bool has_direction(DIRECTIONS dir) const;
    bool collides(DIRECTIONS dir) const;

    bool destroy();
};

#endif  // SRC_MECHANICS_HEADERS_MAP_WALL_H_
