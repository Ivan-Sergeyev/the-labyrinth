#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <algorithm>

#include "directions.h"
#include "treasure.h"


using std::max;
using std::min;


#define MAX_BOMBS 3
#define MAX_BULLETS 3
#define MAX_KNIVES 3

#define START_BOMBS 0
#define START_BULLETS 0
#define START_KNIVES 0

#define HEALTH_MAX 2
#define HEALTH_MIN 1
#define HEALTH_DEATH 0
#define HEALTH_START 2

enum PLAYER_HEALTH_STATES {PHS_ERROR = -1, PHS_DEAD, PHS_WOUNDED,
                           PHS_WELL, PHS_USED_RANGE, PHS_NUM_STATES};


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

    void take_damage(int amount);
    void heal(int amount);

    int add_bombs(int amount);
    int add_bullets(int amount);
    int add_knives(int amount);
    int remove_bombs(int amount);
    int remove_bullets(int amount);
    int remove_knives(int amount);

    bool add_treasure(Treasure *treasure);
};

#endif  // SRC_PLAYER_H_
