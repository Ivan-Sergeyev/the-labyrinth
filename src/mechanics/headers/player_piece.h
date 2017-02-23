#ifndef SRC_MECHANICS_HEADERS_PLAYER_PIECE_H_
#define SRC_MECHANICS_HEADERS_PLAYER_PIECE_H_

#include "directions.h"


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


enum PLAYER_HEALTH_STATE {
    PHS_ERROR = -1,
    PHS_DEAD, PHS_WOUNDED, PHS_WELL,
    PHS_NUM_STATES
};

enum PLAYER_ACTION {
    ACT_NONE = -1,
    ACT_SKIP, ACT_MOVE,
    ACT_KNIFE, ACT_SHOOT, ACT_BOMB,
    ACT_NUMBER
};


class player_move_t {
 public:
    PLAYER_ACTION action;
    DIRECTION direction;

    player_move_t();
    player_move_t(const player_move_t &other);
    player_move_t(const PLAYER_ACTION &a, const DIRECTION &d);

    player_move_t& operator = (const player_move_t &other);
};


class PlayerPiece {
 private:
    int _x_pos, _y_pos;
    int _health;
    int _bombs, _bullets, _knives;

    PLAYER_HEALTH_STATE _get_health_state() const;
    int _health_in_range(int health) const;

 public:
    PlayerPiece();

    int get_x_pos() const;
    int get_y_pos() const;

    bool is_alive() const;
    int get_bombs() const;
    int get_bullets() const;
    int get_knives() const;

    void set_pos(int x, int y);

    void set_health(int amount);
    void take_damage(int amount);
    void heal(int amount);

    int add_bombs(int amount);
    int add_bullets(int amount);
    int add_knives(int amount);
    int remove_bombs(int amount);
    int remove_bullets(int amount);
    int remove_knives(int amount);
};

#endif  // SRC_MECHANICS_HEADERS_PLAYER_PIECE_H_
