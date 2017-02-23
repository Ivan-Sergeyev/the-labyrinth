#include "../headers/gamestate.h"


bool Gamestate::_check_initialization() {
    if (!_game_map.is_initialized() ||
        (_num_players == 0) || (_players == nullptr)) {
        return false;
    }
    return true;
}

void _resize_players(int size) {
    // todo : implement
}

void Gamestate::_start_next_turn(OUTCOMES outcome) {
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
        if ((_players[i]->get_x_pos() == x) &&
            (_players[i]->get_y_pos() == y) &&
            (i != player_id)) {
            _had_other_players = true;
            _players[i]->take_damage(1);
        }
    }
    return _had_other_players;
}

Gamestate::Gamestate() :
    _num_treasures(0), _treasures(nullptr),
    _player_turn(0), _num_players(0), _players(nullptr)
    {}

Gamestate::~Gamestate() {
    _game_map.~GameMap();
    delete[] _treasures;
    delete[] _players;
}

void Gamestate::init(int x_size, int y_size,
                     int num_treasures, int num_players) {
    _game_map.init(x_size, y_size);

    _num_treasures = num_treasures;
    _treasures = new Treasure[_num_treasures];

    _num_players = num_players;
    _players = new Player*[_num_players];
}

void Gamestate::set_players(Player **players) {
    for (int i = 0; i < _num_players; ++i) {
        _players[i] = players[i];
    }
}

int Gamestate::get_player_id(const Player &player) const {
    for (int i = 0; i < _num_players; ++i) {
        if (_players[i] == &player) {
            return i;
        }
    }
    return -1;
}

bool Gamestate::generate_map() {
    // todo : pass parameters
    return _game_map.generate();
}

int Gamestate::load_map(const char *filename) {
    return _game_map.load(filename);
}

OUTCOMES Gamestate::attempt_move(int player_id, player_move_t p_move) {
    if (!_check_initialization()) {
        return OUT_INVALID;
    }

    if (player_id != _player_turn) {
        return OUT_IGNORED;
    }

    OUTCOMES outcome = OUT_INVALID;
    Player &player = *_players[player_id];
    int player_x = player.get_x_pos();
    int player_y = player.get_y_pos();

    switch (p_move.action) {
    case ACT_NONE:
        break;
    case ACT_SKIP:
        // skip turn
        outcome = OUT_SKIP;
        break;
    case ACT_MOVE:
        if (!is_direction(p_move.direction)) {
            break;
        }
        // attempt to move player
        if (_game_map.can_move(player_x, player_y, p_move.direction)) {
            player_x += DIRECTIONS_X[p_move.direction];
            player_y += DIRECTIONS_Y[p_move.direction];
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
        if (!is_direction(p_move.direction)) {
            break;
        }
        // attempt to shoot a bullet
        outcome = OUT_MISS;
        break;
        outcome = OUT_WOUND;
        break;
        outcome = OUT_KILL;
        break;
    case ACT_BOMB:
        if (!is_direction(p_move.direction)) {
            break;
        }
        // attempt to use a bomb
        outcome = OUT_BOMB_FAIL;
        break;
        outcome = OUT_BOMB_SUCCESS;
        break;
    default:
        break;
    }

    _start_next_turn(outcome);

    return outcome;
}
