#ifndef SRC_MECHANICS_HEADERS_MAP_TILE_H_
#define SRC_MECHANICS_HEADERS_MAP_TILE_H_

#include "map_wall.h"


enum MAP_TILE_TYPES {
    MTT_UNDEFINED = -1,
    MTT_EMPTY, MTT_HOLE,
    MTT_RIVER, MTT_RIVER_SOURCE, MTT_RIVER_MOUTH,
    MTT_HOSPITAL, MTT_ARMORY, MTT_EXIT
};


class MapTile {
 private:
    MAP_TILE_TYPES _type;
    MapWall walls[DIR_NUM_DIRECTIONS];

 public:
    MapTile();
    explicit MapTile(MAP_TILE_TYPES type);

    MAP_TILE_TYPES get_type() const;

    bool has_wall(DIRECTIONS dir) const;
    bool add_wall(MapWall wall);

    bool destroy_wall_in_direction(DIRECTIONS dir);
};

#endif  // SRC_MECHANICS_HEADERS_MAP_TILE_H_
