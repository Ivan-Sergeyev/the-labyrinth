#include "../headers/gamestate.h"


bool Gamestate::_check_initialization() {
    if (!_map.is_initialized() || (_num_players == 0)) {
        return false;
    }
    return true;
}

void Gamestate::_start_next_turn(OUTCOME outcome) {
    switch (outcome) {
    case OUT_SKIP:
    case OUT_PASS:
    case OUT_WALL:
    case OUT_MISS:
    case OUT_WOUND:
    case OUT_KILL:
    case OUT_BOMB_SUCCESS:
    case OUT_BOMB_FAIL:
        _player_turn = (_player_turn + 1) % _num_players;
        // todo : change positions of treasures
        break;
    case OUT_INVALID:
    case OUT_IGNORED:
    case OUT_NO_TURN:
    default:
        break;
    }
}

bool Gamestate::_wound_other_players(int x, int y, int player_id) {
    bool _had_other_players = false;
    for (int i = 0; i < _num_players; i++) {
        Player *player = &(_players[i]);
        if ((player->get_x_pos() == x) &&
            (player->get_y_pos() == y) &&
            (i != player_id)) {
            _had_other_players = true;
            player->take_damage(1);
        }
    }
    return _had_other_players;
}

Gamestate::Gamestate(int num_players) :
        _num_players(num_players), _player_turn(0),
        _num_treasures(0), _treasure(nullptr) {
    _players = new Player[num_players];
}

Gamestate::~Gamestate() {
    _map.~Map();
    delete[] _treasure;
    delete[] _players;
}

bool Gamestate::generate_map(int x_size, int y_size) {
    _map.init(x_size, y_size);
    // todo : pass parameters
    return _map.generate();
}

int Gamestate::load_map(const char *filename) {
    return _map.load(filename);
}

int Gamestate::save_map(const char *filename) const {
    return _map.save(filename);
}

OUTCOME Gamestate::_try_shoot(int player_id, DIRECTION dir) {
    if (_players[player_id].get_bullets() == 0) {
        return OUT_INVALID;
    }
    int x = _players[player_id].get_x_pos();
    int y = _players[player_id].get_y_pos();

    while (!_map.can_move(x, y, dir)) {
        x += DIRECTION_DX[dir];
        y += DIRECTION_DY[dir];

        if (_wound_other_players(x, y, player_id)) {
            return OUT_WOUND;
        }
    }

    return OUT_MISS;
}

OUTCOME Gamestate::request_move(int player_id, player_move_t p_move) {
    if (!_check_initialization()) {
        return OUT_INVALID;
    }

    if (player_id != _player_turn) {
        return OUT_IGNORED;
    }

    OUTCOME outcome = OUT_INVALID;
    Player &player = _players[player_id];
    int player_x = player.get_x_pos();
    int player_y = player.get_y_pos();
    DIRECTION player_d = p_move.direction;

    // needed for bomb action
    MapWall _map_wall = _map.get_wall(player_x, player_y, player_d);

    switch (p_move.action) {
    case ACT_NONE:
        break;
    case ACT_SKIP:
        // skip turn
        outcome = OUT_SKIP;
        break;
    case ACT_MOVE:
        if (!is_direction(player_d)) {
            break;
        }
        // attempt to move player
        if (_map.can_move(player_x, player_y, player_d)) {
            player_x += DIRECTION_DX[player_d];
            player_y += DIRECTION_DY[player_d];
            player.set_pos(player_x, player_y);
            // todo : move player's treasure with them
            outcome = OUT_PASS;
        } else {
            outcome = OUT_WALL;
        }
        break;
    case ACT_KNIFE:
        // attempt to use a knife
        if (!_wound_other_players(player_x, player_y, player_id)) {
            outcome = OUT_MISS;
            break;
        } else {
            outcome = OUT_WOUND;
            break;
        }
        // outcome = OUT_KILL;
        // break;
    case ACT_SHOOT:
        if (!is_direction(player_d)) {
            break;
        }

        outcome = _try_shoot(player_id, player_d);
    break;

    case ACT_BOMB:
        if (!is_direction(player_d)) {
            break;
        }
        // attempt to use a bomb
        if ((!_map_wall.exists()) ||
            (_map_wall.get_type() != WT_DESTRUCTIBLE)) {
                outcome = OUT_BOMB_FAIL;
        } else {
                outcome = OUT_BOMB_SUCCESS;
        }
        break;

    default:
        break;
    }

    _start_next_turn(outcome);

    return outcome;
}
