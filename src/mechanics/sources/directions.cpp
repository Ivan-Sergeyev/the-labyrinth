#include "../headers/directions.h"


bool is_direction(const DIRECTION &direction) {
    return direction != DIR_NONE && direction != DIR_NUMBER;
}
