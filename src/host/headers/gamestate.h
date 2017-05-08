#ifndef SRC_HOST_HEADERS_GAMESTATE_H_
#define SRC_HOST_HEADERS_GAMESTATE_H_

#include "map.h"
#include "player.h"
#include "treasure.h"


enum OUTCOME {
    OUT_INVALID = 0, OUT_IGNORED, OUT_NO_TURN,
    OUT_SKIP,
    OUT_PASS, OUT_WALL,
    OUT_MISS, OUT_WOUND, OUT_KILL,
    OUT_BOMB_SUCCESS, OUT_BOMB_FAIL,
    OUT_NUMBER
};


class Gamestate {
 private:
    Map _map;

    int _num_players;
    Player *_players;

    int _num_treasures;
    Treasure *_treasure;

 public:
    explicit Gamestate(int num_players);
    ~Gamestate();

    bool is_initialized();

    bool generate_map(int x_size, int y_size);
    int load_map(const char *filename);
    int save_map(const char *filename) const;

    // todo : move these to rules or host
    OUTCOME _wound_other_players(int x, int y, int player_id);
    OUTCOME _try_shoot(int player_id, DIRECTION dir);
    OUTCOME _request_move(int player_id, player_move_t p_move);
};

#endif  // SRC_HOST_HEADERS_GAMESTATE_H_
