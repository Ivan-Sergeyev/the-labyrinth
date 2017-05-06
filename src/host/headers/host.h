#ifndef SRC_HOST_HOST_H_
#define SRC_HOST_HOST_H_

#include <vector>
#include <sys/types.h>
#include <sys/socket.h>

#include "gamestate.h"

using std::vector;


class Host {
 private:
    int _num_players;
    vector<int> _player_socket_fds;

    Gamestate *_gamestate;

    // todo : add ruleset

    void _reserve_player_sockets();

    void _init_gamestate();
    void _delete_gamesate();

 public:
    // todo : init with sockfd of the hosting player

    ~Host();

    // todo : change number of players
    // todo : add players
    // todo : change settings/rules

    // todo : game cycle
};

#endif  // SRC_HOST_HOST_H_
