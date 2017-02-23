#ifndef SRC_MECHANICS_HEADERS_MAP_TILE_H_
#define SRC_MECHANICS_HEADERS_MAP_TILE_H_

#include "map_wall.h"


enum MAP_TILE_TYPE {
    MTT_UNDEFINED = -1,
    MTT_FREE, MTT_HOLE,
    MTT_RIVER, MTT_RIVER_START, MTT_RIVER_END,
    MTT_MEDBAY, MTT_ARMORY, MTT_EXIT,
    MTT_NUMBER
};

const char MTT_SYMBOL[MTT_NUMBER] = {
    'F', 'H', 'R', 'S', 'E', 'M', 'A', 'e'
};

MAP_TILE_TYPE get_tile_type_by_symbol(char c);


class MapTile {
 private:
    MAP_TILE_TYPE _type;
    MapTile *_next;
    MapWall _walls[DIR_NUMBER];

 public:
    MapTile();
    explicit MapTile(MAP_TILE_TYPE type);

    void clear();

    MAP_TILE_TYPE get_type() const;
    MapTile* get_next() const;
    bool has_wall(DIRECTION dir) const;

    void set_type(MAP_TILE_TYPE type);
    void set_next(MapTile *next);
    bool add_wall(MapWall wall);
    bool destroy_wall_in_direction(DIRECTION dir);

    MapWall& get_wall(DIRECTION dir);
};

#endif  // SRC_MECHANICS_HEADERS_MAP_TILE_H_
