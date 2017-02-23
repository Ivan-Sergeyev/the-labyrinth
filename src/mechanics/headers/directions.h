#ifndef SRC_MECHANICS_HEADERS_DIRECTIONS_H_
#define SRC_MECHANICS_HEADERS_DIRECTIONS_H_

enum DIRECTION {
    DIR_NONE = -1, DIR_LEFT, DIR_UP, DIR_DOWN, DIR_RIGHT, DIR_NUMBER
};

const int DIRECTION_DX[DIR_NUMBER] = {
    -1, 0, 0, 1
};

const int DIRECTION_DY[DIR_NUMBER] = {
    0, -1, 1, 0
};

const char DIRECTION_STRING[DIR_NUMBER][6] = {
    "left", "up", "down", "right"
};

const char DIRECTION_SYMBOL[DIR_NUMBER] {
    '<', '^', 'V', '>'
};

bool is_direction(const DIRECTION &direction);

DIRECTION get_direction_by_symbol(char c);

#endif  // SRC_MECHANICS_HEADERS_DIRECTIONS_H_
