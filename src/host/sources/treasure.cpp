#include "../headers/treasure.h"

Treasure::Treasure() : _x_pos(0), _y_pos(0), _is_fake(false) {
}

void Treasure::set_fake(bool fake) {
    _is_fake = fake;
}

void Treasure::set_pos(int x, int y) {
    _x_pos = x;
    _y_pos = y;
}
