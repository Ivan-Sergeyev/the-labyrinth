#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <algorithm>

#include "treasure.h"


// todo : implement these defines as game settings stored in gamestate
#define MAX_BOMBS 3
#define MAX_BULLETS 3
#define MAX_KNIVES 3

#define START_BOMBS 0
#define START_BULLETS 0
#define START_KNIVES 0

#define HEALTH_START 1


enum PLAYER_HEALTH_STATES {PHS_ERROR = -1, PHS_DEAD, PHS_WOUNDED,
                           PHS_WELL, PHS_USED_RANGE, PHS_NUM_STATES};
const int HEALTH_RANGES[PHS_NUM_STATES][2] = \
    {{-1, -1}, {0, 0}, {1, 1}, {0, 1}};


// todo : move implementations to player.cpp
class Player {
 private:
    int _x_pos, _y_pos;

    int _health;

    int _bombs, _bullets, _knives;

    bool _has_treasure;
    Treasure *_treasure;


    PLAYER_HEALTH_STATES _get_health_state() const {
        int state;
        for (state = PHS_DEAD; state != PHS_USED_RANGE; ++state) {
            if (HEALTH_RANGES[0][state] <= _health &&
                HEALTH_RANGES[1][state] >= _health) {
              return (PLAYER_HEALTH_STATES) state;
            }
        }
        return PHS_ERROR;
    }

    int _health_in_range(int health) const {
        if (health < HEALTH_RANGES[0][PHS_USED_RANGE]) {
            return HEALTH_RANGES[0][PHS_USED_RANGE];
        }
        if (health > HEALTH_RANGES[1][PHS_USED_RANGE]) {
            return HEALTH_RANGES[1][PHS_USED_RANGE];
        }
        return health;
    }

 public:
    Player(int x, int y) :
        _x_pos(x), _y_pos(y), _health(HEALTH_START),
        _bombs(START_BOMBS), _bullets(START_BULLETS), _knives(START_KNIVES),
        _has_treasure(0), _treasure(0)
        {}


    int get_x_pos() const {
        return _x_pos;
    }

    int get_y_pos() const {
        return _y_pos;
    }

    bool is_alive() const {
        return _get_health_state() != PHS_DEAD;
    }

    int get_bombs() const {
        return _bombs;
    }

    int get_bullets() const {
        return _bullets;
    }

    int get_knives() const {
        return _knives;
    }

    bool has_treasure() const {
        return _has_treasure;
    }

    Treasure* carried_treasure() const {
        return _treasure;
    }


    void move(int new_x, int new_y) {
        _x_pos = new_x;
        _y_pos = new_y;
    }

    void take_damage(int amount = 1) {
        _health = _health_in_range(_health - amount);
    }

    void heal(int amount = 1) {
        _health = _health_in_range(_health + amount);
    }

    int add_bombs(int amount) {
        int bombs_added = std::min(MAX_BOMBS - _bombs, amount);
        _bombs += bombs_added;
        return bombs_added;
    }

    int add_bullets(int amount) {
        int bullets_added = std::min(MAX_BULLETS - _bullets, amount);
        _bullets += bullets_added;
        return bullets_added;
    }

    int add_knives(int amount) {
        int knives_added = std::min(MAX_KNIVES - _knives, amount);
        _knives += knives_added;
        return knives_added;
    }

    int remove_bombs(int amount) {
        int bombs_removed = std::min(_bombs, amount);
        _bombs -= bombs_removed;
        return bombs_removed;
    }

    int remove_bullets(int amount) {
        int bullets_removed = std::min(_bullets, amount);
        _bullets -= bullets_removed;
        return bullets_removed;
    }

    int remove_knives(int amount) {
        int knives_removed = std::min(_knives, amount);
        _knives -= knives_removed;
        return knives_removed;
    }

    bool add_treasure(Treasure *treasure) {
        if (_has_treasure || _get_health_state() != PHS_WELL) {
            return 0;
        }

        _has_treasure = 1;
        _treasure = treasure;
        return 1;
    }
};

#endif  // SRC_PLAYER_H_
