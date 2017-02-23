#ifndef SRC_MECHANICS_HEADERS_DIRECTIONS_H_
#define SRC_MECHANICS_HEADERS_DIRECTIONS_H_

enum DIRECTIONS {
    DIR_NONE = -1, DIR_LEFT, DIR_UP, DIR_DOWN, DIR_RIHGT, DIR_NUM_DIRECTIONS
};

const char directions_strings[DIR_NUM_DIRECTIONS][6] = {
    "left", "up", "down", "right"
};

bool is_direction(const DIRECTIONS &direction);

#endif  // SRC_MECHANICS_HEADERS_DIRECTIONS_H_
