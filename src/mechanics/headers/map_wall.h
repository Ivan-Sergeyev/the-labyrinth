#ifndef SRC_MECHANICS_HEADERS_MAP_WALL_H_
#define SRC_MECHANICS_HEADERS_MAP_WALL_H_

#include "directions.h"


enum MAP_WALL_TYPE {
    WT_UNDEFINED = -1,
    WT_DESTRUCTIBLE, WT_INDESTRUCTIBLE, WT_MONOLYTH, WT_EXIT
};


class MapWall {
 private:
    DIRECTION _direction;
    MAP_WALL_TYPE _type;
    bool _enabled;

 public:
    MapWall();
    MapWall(DIRECTION dir, MAP_WALL_TYPE type, bool enabled = true);
    MapWall(const MapWall &other);

    ~MapWall();

    void clear();

    DIRECTION get_direction() const;
    MAP_WALL_TYPE get_type() const;
    bool get_enabled() const;

    bool exists() const;
    bool has_direction(DIRECTION dir) const;
    bool collides(DIRECTION dir) const;

    bool destroy();
};

#endif  // SRC_MECHANICS_HEADERS_MAP_WALL_H_
