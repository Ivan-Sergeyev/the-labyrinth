#include <algorithm>

#include "../headers/player.h"

using std::max;
using std::min;


player_move_t::player_move_t() :
    action(ACT_NONE), direction(DIR_NONE) {}

player_move_t::player_move_t(const player_move_t &other) :
    action(other.action), direction(other.direction) {}

player_move_t::player_move_t(const PLAYER_ACTIONS &a, const DIRECTIONS &d) :
    action(a), direction(d) {}

player_move_t& player_move_t::operator = (const player_move_t &other) {
    if (this != &other) {
        action = other.action;
        direction = other.direction;
    }
    return *this;
}


PLAYER_HEALTH_STATES Player::_get_health_state() const {
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

int Player::_health_in_range(int health) const {
    return max(min(health, HEALTH_MAX), HEALTH_MIN);
}

Player::Player() :
    _x_pos(0), _y_pos(0), _health(0),
    _bombs(0), _bullets(0), _knives(0),
    _has_treasure(false), _treasure(nullptr) {}

int Player::get_x_pos() const {
    return _x_pos;
}

int Player::get_y_pos() const {
    return _y_pos;
}

bool Player::is_alive() const {
    return _get_health_state() != PHS_DEAD;
}

int Player::get_bombs() const {
    return _bombs;
}

int Player::get_bullets() const {
    return _bullets;
}

int Player::get_knives() const {
    return _knives;
}

bool Player::has_treasure() const {
    return _has_treasure;
}

Treasure* Player::carried_treasure() const {
    return _treasure;
}

void Player::set_pos(int x, int y) {
    _x_pos = x;
    _y_pos = y;
}

void Player::set_health(int amount) {
    _health = _health_in_range(amount);
}

void Player::take_damage(int amount) {
    _health = _health_in_range(_health - amount);
}

void Player::heal(int amount) {
    _health = _health_in_range(_health + amount);
}

int Player::add_bombs(int amount) {
    int bombs_added = min(MAX_BOMBS - _bombs, amount);
    _bombs += bombs_added;
    return bombs_added;
}

int Player::add_bullets(int amount) {
    int bullets_added = min(MAX_BULLETS - _bullets, amount);
    _bullets += bullets_added;
    return bullets_added;
}

int Player::add_knives(int amount) {
    int knives_added = min(MAX_KNIVES - _knives, amount);
    _knives += knives_added;
    return knives_added;
}

int Player::remove_bombs(int amount) {
    int bombs_removed = min(_bombs, amount);
    _bombs -= bombs_removed;
    return bombs_removed;
}

int Player::remove_bullets(int amount) {
    int bullets_removed = min(_bullets, amount);
    _bullets -= bullets_removed;
    return bullets_removed;
}

int Player::remove_knives(int amount) {
    int knives_removed = min(_knives, amount);
    _knives -= knives_removed;
    return knives_removed;
}

bool Player::add_treasure(Treasure *treasure) {
    if (_has_treasure || _get_health_state() != PHS_WELL) {
        return false;
    }

    _has_treasure = true;
    _treasure = treasure;
    return true;
}
