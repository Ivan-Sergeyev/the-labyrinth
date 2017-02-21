#include "player.h"


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

Player::Player(int x, int y) :
    _x_pos(x), _y_pos(y), _health(HEALTH_START),
    _bombs(START_BOMBS), _bullets(START_BULLETS), _knives(START_KNIVES),
    _has_treasure(false), _treasure(NULL)
    {}

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

void Player::move(int new_x, int new_y) {
    _x_pos = new_x;
    _y_pos = new_y;
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
