#include "../headers/directions.h"


bool is_direction(const DIRECTION &direction) {
    return direction != DIR_NONE && direction != DIR_NUMBER;
}

DIRECTION get_direction_by_symbol(char c) {
    for (int d = 0; d < DIR_NUMBER; ++d) {
        if (DIRECTION_SYMBOL[d] == c) {
            return (DIRECTION) d;
        }
    }
    return DIR_NONE;
}
