#ifndef SRC_MECHANICS_HEADERS_GAMESTATE_H_
#define SRC_MECHANICS_HEADERS_GAMESTATE_H_

#include "game_map.h"
#include "player_piece.h"
#include "treasure.h"


enum OUTCOME {
    OUT_INVALID = 0, OUT_IGNORED, OUT_NO_TURN,
    OUT_SKIP,
    OUT_PASS, OUT_WALL,
    OUT_MISS, OUT_WOUND, OUT_KILL,
    OUT_BOMB_SUCCESS, OUT_BOMB_FAIL,
    OUT_NUMBER
};

const char OUTCOME_STRING[OUT_NUMBER][30] = {
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


class Gamestate {
 private:
    GameMap _game_map;

    int _num_players;
    PlayerPiece _player_pieces[1];
    int _player_turn;

    int _num_treasures;
    Treasure *_treasure;

    // todo : interfaces for talking to local and remote players

    bool _check_initialization();

    void _start_next_turn(OUTCOME outcome);
    bool _wound_other_players(int x, int y, int player_id);
    OUTCOME _try_shoot(int player_id, DIRECTION dir);

 public:
    Gamestate();

    ~Gamestate();

    bool generate_map(int x_size, int y_size);
    int load_map(const char *filename);
    int save_map(const char *filename) const;

    OUTCOME request_move(int player_id, player_move_t p_move);
};

#endif  // SRC_MECHANICS_HEADERS_GAMESTATE_H_
