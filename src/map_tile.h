#ifndef SRC_MAP_TILE_H_
#define SRC_MAP_TILE_H_

enum MAP_TILE_TYPES {
    TILE_UNDEFINED = -1,                   // utility
    TILE_EMPTY, TILE_HOLE, TILE_RIVER,     // landscape
    TILE_HOSPITAL, TILE_ARMORY, TILE_EXIT  // special
};


class MapTile {
 private:
    MAP_TILE_TYPES _type;

 public:
    MapTile() : _type(TILE_UNDEFINED) {}

    MapTile(MAP_TILE_TYPES type) : _type(type) {}

    MAP_TILE_TYPES get_type() const {
        return _type;
    }
};

#endif  // SRC_MAP_TILE_H_
