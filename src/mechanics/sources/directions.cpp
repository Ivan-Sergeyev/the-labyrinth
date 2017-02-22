#include "../headers/directions.h"


bool is_direction(const DIRECTIONS &direction) {
    return direction != DIR_NONE && direction != DIR_NUM_DIRECTIONS;
}
