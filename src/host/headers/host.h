#ifndef SRC_HOST_HEADERS_HOST_H_
#define SRC_HOST_HEADERS_HOST_H_

#include <string>
#include <vector>

#include "socket_common.h"
#include "gamestate.h"

using std::string;
using std::vector;


// todo : use array of strings
const int OUTCOME_STR_MAX_LEN = 30;
const char OUTCOME_STRING[OUT_NUMBER][OUTCOME_STR_MAX_LEN] = {
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


class Host {
 private:
    int _listen_sock_fd;
    int _num_players;
    int _max_num_players;

    // todo : move to class player? (all info about player in one place)
    vector<int> _player_socket_fds;

    Gamestate *_gamestate;

    // todo : add ruleset

    int _player_turn;

    void _reserve_player_sockets();
    void _close_connections();

    int _start_listener();
    int _connect_hosting_player();

    void _init_gamestate();
    // todo : generate gamestate
    void _delete_gamesate();

    // todo : setup loop
    // todo : change number of players
    // todo : change settings/rules
    // todo : add other players

    void _game_loop();

    player_move_t _parse_input(const vector<string> &words) const;
    // todo : remove copies of these from gamestate
    void _start_next_turn(OUTCOME outcome);
    bool _wound_other_players(int x, int y, int player_id);
    OUTCOME _try_shoot(int player_id, DIRECTION dir);
    OUTCOME _request_move(int player_id, player_move_t p_move);

 public:
    Host();
    ~Host();

    int start();
    int run();
};

#endif  // SRC_HOST_HEADERS_HOST_H_
