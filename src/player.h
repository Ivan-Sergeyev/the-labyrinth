#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "treasure.h"


// todo : implement these as game settings
#define MAX_HEALTH 1
#define MIN_HEALTH 0
#define DEATH_HEALTH -1
#define STARTING_HEALTH 1

#define MAX_BOMBS 3
#define MAX_BULLETS 3
#define MAX_KNIVES 3

#define STARTING_BOMBS 0
#define STARTING_BULLETS 0
#define STARTING_KNIVES 0


class Player {
 private:
    int _is_alive;
    int _x_pos, _y_pos;
    int _health;
    int _bombs, _bullets, _knives;
    int _has_treasure;
    Treasure *_treasure;

 public:
    Player(int x, int y) :
        _x_pos(x), _y_pos(y), _health(STARTING_HEALTH), _is_alive(1),
        bombs(STARTING_BOMBS), bullets(STARTING_BULLETS),
        knives(STARTING_KNIVES)
        {}

    void take_damage(int amount = 1) {
        _health -= amount;
        if (_health < MIN_HEALTH) {
            _health = MIN_HEALTH;
        }
        if (_health == DEATH_HEALTH) {
            _is_alive = 0;
        }
    }

    void heal(int amount = 1) {
        _health += amount;
        if (_health > MAX_HEALTH) {
            _health = MAX_HEALTH;
        }
        _is_alive = 1;
    }

    void move(int new_x, int new_y) {
        _x_pos = new_x;
        _y_pos = new_y;
    }

    void add_bombs(int amount) {
        _bombs += amount;
    }

    void add_bullets(int amount) {
        _bullets += amount;
    }

    void add_knives(int amount) {
        _knives += amount;
    }

    void add_treasure(Treasure *treasure) {
        _has_treasure = 1;
        _treasure = treasure;
    }
}

#endif  // SRC_PLAYER_H_
