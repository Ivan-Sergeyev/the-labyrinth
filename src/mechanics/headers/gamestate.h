#ifndef SRC_MECHANICS_HEADERS_GAMESTATE_H_
#define SRC_MECHANICS_HEADERS_GAMESTATE_H_

#include "map_tile.h"
#include "player.h"


enum OUTCOMES {
    OUT_INVALID = 0, OUT_IGNORE, OUT_NO_TURN,
    OUT_SKIP,
    OUT_PASS, OUT_WALL,
    OUT_MISS, OUT_WOUND, OUT_KILL,
    OUT_BOMB_SUCCESS, OUT_BOMB_FAIL,
    OUT_NUM_OUTCOMES
};


const char outcomes_strings[OUT_NUM_OUTCOMES][30] = {
    "your command is invalid",
    "command ignored",
    "it is not your turn",
    "you skip your turn",
    "you pass to the next tile",
    "you bump into a wall",
    "you miss",
    "you wound another player",
    "you kill another player",
    "you blow up a wall",
    "you fail to blow up a wall"
};



bool retry_turn(const OUTCOMES &outcome);

class Gamestate {
 private:
    int _x_size, _y_size;

    MapTile **_tiles;

    int _num_treasures;
    Treasure *_treasures;

    int _num_players;
    Player **_players;

    void _pass_turn_to_next_player();
    bool _has_wall(int x, int y, DIRECTIONS direction);
    bool _wound_other_players(int x, int y, int player_id);
    bool _check_initialization();

 public:
    Gamestate();

    ~Gamestate();
    void init(int x_size, int y_size, int num_treasures, int num_players);

    void set_players(Player **players);

    int get_player_id(const Player &player);

    void generate_map();

    OUTCOMES attempt_move(int player_id, player_move_t p_move);
};

#endif  // SRC_MECHANICS_HEADERS_GAMESTATE_H_
