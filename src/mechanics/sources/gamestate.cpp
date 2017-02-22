#include "../headers/gamestate.h"

bool retry_turn(const OUTCOMES &outcome) {
    return outcome == OUT_INVALID || outcome == OUT_NUM_OUTCOMES;
}


void Gamestate::_pass_turn_to_next_player() {
    // todo : implement
}

bool Gamestate::_has_wall(int x, int y, DIRECTIONS direction) {
    return _tiles[x][y].has_wall(direction);
}

bool Gamestate::_wound_other_players(int x, int y, int player_id) {
    bool _had_other_players = false;
    for(int i = 0; i < _num_players; i++)
    {
	if((_players[i]->get_x_pos() == x) &&
	   (_players[i]->get_y_pos() == y) &&
	   (i != player_id)) {
	    _had_other_players = true;
	    _players[i]->take_damage(1);
	}

    }
    return _had_other_players;
}

bool Gamestate::_check_initialization()
{
    if ((_x_size == 0) ||
	(_y_size == 0) ||
	(_tiles == nullptr) ||
	(_num_players == 0) ||
	(_players == nullptr))
	return false;
    return true;
}

Gamestate::Gamestate() :
    _x_size(0), _y_size(0), _tiles(nullptr),
    _num_treasures(0), _treasures(nullptr),
    _num_players(0), _players(nullptr)
    {}

Gamestate::~Gamestate() {
    if (_tiles) {
	for (int i = 0; i < _x_size; ++i) {
	    delete[] _tiles[i];
	}
	delete[] _tiles;
    }

    delete[] _treasures;
    delete[] _players;
}

void Gamestate::init(int x_size, int y_size, int num_treasures, int num_players) {
    _x_size = x_size;
    _y_size = y_size;
    _tiles = new MapTile*[_x_size];
    for (int i = 0; i < _x_size; ++i) {
	_tiles[i] = new MapTile[_y_size];
    }

    _num_treasures = num_treasures;
    _treasures = new Treasure[num_treasures];

    _num_players = num_players;
    _players = new Player*[num_players];
}

void Gamestate::set_players(Player **players) {
    for (int i = 0; i < _num_players; ++i) {
	_players[i] = players[i];
    }
}

int Gamestate::get_player_id(const Player &player) {
    for (int i = 0; i < _num_players; ++i) {
	if (_players[i] == &player) {
	    return i;
	}
    }
    return -1;
}

void Gamestate::generate_map() {
    // todo : implement
    // todo : add other parameters -- number of special tiles of each type,
    //        number of treasures, etc.
}

OUTCOMES Gamestate::attempt_move(int player_id, player_move_t p_move) {
    if (!_check_initialization()) {
	return OUT_INVALID;
    }
    // todo : check if it is player's turn

    OUTCOMES outcome = OUT_INVALID;
    Player &player = *_players[player_id];

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
	if (_has_wall(player.get_x_pos(), player.get_y_pos(), p_move.direction)) {
	    outcome = OUT_WALL;
	}
	else {
	    outcome = OUT_PASS;
	}
	break;
    case ACT_KNIFE:
	// attempt to use a knife
	if (!_wound_other_players(player.get_x_pos(), player.get_y_pos(), player_id)) {
	    outcome = OUT_MISS;
	    break;
	}
	else {
	    outcome = OUT_WOUND;
	    break;
	}
	//outcome = OUT_KILL;
	//break;
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

    if (!retry_turn(outcome)) {
	_pass_turn_to_next_player();
    }

    return outcome;
}
