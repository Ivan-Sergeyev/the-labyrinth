#ifndef SRC_MECHANICS_HEADERS_MAP_TILE_H_
#define SRC_MECHANICS_HEADERS_MAP_TILE_H_

#include "map_wall.h"


enum MAP_TILE_TYPES {
    MTT_UNDEFINED = -1,
    MTT_FREE, MTT_HOLE,
    MTT_RIVER, MTT_RIVER_SOURCE, MTT_RIVER_MOUTH,
    MTT_MEDBAY, MTT_ARMORY, MTT_EXIT
};


class MapTile {
 private:
    MAP_TILE_TYPES _type;
    MapWall _walls[DIR_NUM_DIRECTIONS];
    MapTile *_next;

 public:
    MapTile();
    explicit MapTile(MAP_TILE_TYPES type);

    MAP_TILE_TYPES get_type() const;
    MapTile* get_next() const;
    bool has_wall(DIRECTIONS dir) const;

    void set_next(MapTile *next);
    bool add_wall(MapWall wall);
    bool destroy_wall_in_direction(DIRECTIONS dir);

};

#endif  // SRC_MECHANICS_HEADERS_MAP_TILE_H_
