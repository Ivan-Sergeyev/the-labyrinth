#ifndef SRC_MAP_TILE_H_
#define SRC_MAP_TILE_H_

#include <vector>

#include "map_wall.h"

using std::vector;


enum MAP_TILE_TYPES {
    MTT_UNDEFINED = -1,
    MTT_EMPTY, MTT_HOLE,
    MTT_RIVER, MTT_RIVER_SOURCE, MTT_RIVER_MOUTH,
    MTT_HOSPITAL, MTT_ARMORY, MTT_EXIT
};


class MapTile {
 private:
    MAP_TILE_TYPES _type;
    vector <MapWall> walls;

    vector <MapWall>::const_iterator find_wall(DIRECTIONS dir) const;
    vector <MapWall>::iterator find_wall(DIRECTIONS dir);

 public:
    MapTile();
    explicit MapTile(MAP_TILE_TYPES type);

    ~MapTile();

    MAP_TILE_TYPES get_type() const;

    bool has_wall(DIRECTIONS dir) const;
    bool add_wall(MapWall wall);

    bool destroy_wall_in_direction(DIRECTIONS dir);
};

#endif  // SRC_MAP_TILE_H_
