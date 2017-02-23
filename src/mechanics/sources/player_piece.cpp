#include <algorithm>

#include "../headers/player_piece.h"

using std::max;
using std::min;


player_move_t::player_move_t() :
    action(ACT_NONE), direction(DIR_NONE) {}

player_move_t::player_move_t(const player_move_t &other) :
    action(other.action), direction(other.direction) {}

player_move_t::player_move_t(const PLAYER_ACTION &a, const DIRECTION &d) :
    action(a), direction(d) {}

player_move_t& player_move_t::operator = (const player_move_t &other) {
    if (this != &other) {
        action = other.action;
        direction = other.direction;
    }
    return *this;
}


PLAYER_HEALTH_STATE PlayerPiece::_get_health_state() const {
    if (_health == HEALTH_MAX) {
        return PHS_WELL;
    }
    if (_health == HEALTH_DEATH) {
        return PHS_DEAD;
    }
    if (_health > HEALTH_DEATH && _health < HEALTH_MAX) {
        return PHS_WOUNDED;
    }
    return PHS_ERROR;
}

int PlayerPiece::_health_in_range(int health) const {
    return max(min(health, HEALTH_MAX), HEALTH_MIN);
}

PlayerPiece::PlayerPiece() :
    _x_pos(0), _y_pos(0), _health(HEALTH_START),
    _bombs(START_BOMBS), _bullets(START_BULLETS), _knives(START_KNIVES) {}

int PlayerPiece::get_x_pos() const {
    return _x_pos;
}

int PlayerPiece::get_y_pos() const {
    return _y_pos;
}

bool PlayerPiece::is_alive() const {
    return _get_health_state() != PHS_DEAD;
}

int PlayerPiece::get_bombs() const {
    return _bombs;
}

int PlayerPiece::get_bullets() const {
    return _bullets;
}

int PlayerPiece::get_knives() const {
    return _knives;
}

void PlayerPiece::set_pos(int x, int y) {
    _x_pos = x;
    _y_pos = y;
}

void PlayerPiece::set_health(int amount) {
    _health = _health_in_range(amount);
}

void PlayerPiece::take_damage(int amount) {
    _health = _health_in_range(_health - amount);
}

void PlayerPiece::heal(int amount) {
    _health = _health_in_range(_health + amount);
}

int PlayerPiece::add_bombs(int amount) {
    int bombs_added = min(MAX_BOMBS - _bombs, amount);
    _bombs += bombs_added;
    return bombs_added;
}

int PlayerPiece::add_bullets(int amount) {
    int bullets_added = min(MAX_BULLETS - _bullets, amount);
    _bullets += bullets_added;
    return bullets_added;
}

int PlayerPiece::add_knives(int amount) {
    int knives_added = min(MAX_KNIVES - _knives, amount);
    _knives += knives_added;
    return knives_added;
}

int PlayerPiece::remove_bombs(int amount) {
    int bombs_removed = min(_bombs, amount);
    _bombs -= bombs_removed;
    return bombs_removed;
}

int PlayerPiece::remove_bullets(int amount) {
    int bullets_removed = min(_bullets, amount);
    _bullets -= bullets_removed;
    return bullets_removed;
}

int PlayerPiece::remove_knives(int amount) {
    int knives_removed = min(_knives, amount);
    _knives -= knives_removed;
    return knives_removed;
}
