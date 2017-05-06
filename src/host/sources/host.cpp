#include "../headers/host.h"


void Host::_reserve_player_sockets() {
    _player_socket_fds.reserve(_num_players);
}

void Host::_init_gamestate() {
    // assert(_num_players);
    _gamestate = new Gamestate(_num_players);
}

void Host::_delete_gamesate() {
    delete _gamestate;
}

Host::~Host() {
    // todo : shutdown
    _delete_gamesate();
}
