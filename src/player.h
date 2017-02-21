#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "directions.h"
#include <algorithm>

using std::min;

#include "treasure.h"


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


enum PLAYER_ACTIONS {
    ACT_SKIP = 0, ACT_MOVE,
    ACT_MELEE, ACT_SHOOT, ACT_BOMB
};

enum OUTCOMES {
    OUT_SKIP = 0,
    OUT_PASS, OUT_WALL,
    OUT_WOUND, OUT_KILL,
    OUT_BOMB_SUCCESS, OUT_BOMB_FAIL
};


// todo : move implementations to player.cpp
class Player {
 private:
    int _x_pos, _y_pos;

    int _health;

    int _bombs, _bullets, _knives;

    bool _has_treasure;
    Treasure *_treasure;

    PLAYER_HEALTH_STATES _get_health_state() const; 
    int _health_in_range(int health) const;

public:
    Player(int x, int y);

    int get_x_pos() const;
    int get_y_pos() const;

    bool is_alive() const;
    int get_bombs() const;
    int get_bullets() const;
    int get_knives() const;
    bool has_treasure() const;
    Treasure* carried_treasure() const;
    void move(int new_x, int new_y);
    void take_damage(int amount = 1);
    void heal(int amount = 1);
    int add_bombs(int amount);
    int add_bullets(int amount);
    int add_knives(int amount);
    int remove_bombs(int amount);
    int remove_bullets(int amount);
    int remove_knives(int amount);
    bool add_treasure(Treasure *treasure);
};

#endif  // SRC_PLAYER_H_
