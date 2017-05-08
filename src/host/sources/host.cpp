#include <iostream>
#include <sstream>

#include "../headers/host.h"

using std::cerr;
using std::stringstream;

#define MAXDATASIZE 100  // max number of bytes we can get at once
#define BACKLOG 10       // how many pending connections queue will hold


void _close_sock_fd(int *fd) {
    close(*fd);
    *fd = -1;
}

template<typename Out>
void split(const string &s, char delim, Out result) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

void Host::_reserve_player_sockets() {
    _player_socket_fds.reserve(_max_num_players);
}

void Host::_close_connections() {
    _close_sock_fd(&_listen_sock_fd);

    for (int i = 0; i < _max_num_players; ++i) {
        if (_player_socket_fds[i] != -1) {
            _close_sock_fd(&_player_socket_fds[i]);
        }
    }
}

int Host::_start_listener() {
    struct addrinfo hints, *servinfo, *p;
    int ret;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;  // use my IP

    ret = getaddrinfo(nullptr, PORT, &hints, &servinfo);
    if (ret != 0) {
        cerr << "host : getaddrinfo: " << gai_strerror(ret) << '\n';
        return 1;
    }

    // loop through all the results and bind to the first we can
    int yes = 1;
    for (p = servinfo; p != nullptr; p = p->ai_next) {
        _listen_sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (_listen_sock_fd == -1) {
            perror("host : socket");
            continue;
        }

        ret = setsockopt(_listen_sock_fd, SOL_SOCKET,
                         SO_REUSEADDR, &yes, sizeof(int));
        if (ret == -1) {
            perror("host : setsockopt");
            return 1;
        }

        ret = bind(_listen_sock_fd, p->ai_addr, p->ai_addrlen);
        if (ret == -1) {
            close(_listen_sock_fd);
            perror("host : bind");
            continue;
        }

        break;
    }
    freeaddrinfo(servinfo);  // all done with this structure

    if (p == nullptr)  {
        cerr << "host : failed to bind\n";
        return 1;
    }

    if (listen(_listen_sock_fd, BACKLOG) == -1) {
        perror("host : listen");
        return 1;
    }

    return 0;
}

int Host::_connect_hosting_player() {
    struct sigaction sa;
    sa.sa_handler = _sigchld_handler;  // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, nullptr) == -1) {
        perror("host : sigaction");
        return 1;
    }

    int new_fd;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];

    while (1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(_listen_sock_fd, (struct sockaddr *)&their_addr,
                        &sin_size);
        if (new_fd == -1) {
            perror("host : accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            _get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        cerr << "host : got connection from " << s << '\n';
        break;
    }

    _reserve_player_sockets();
    _player_socket_fds[0] = new_fd;
    return 0;
}

void Host::_init_gamestate() {
    // assert(_num_players);
    _gamestate = new Gamestate(_num_players);
}

void Host::_delete_gamesate() {
    delete _gamestate;
}

void Host::_game_loop() {
    int numbytes;
    char buf[MAXDATASIZE];
    string msg;

    player_move_t move;
    OUTCOME out;

    while (1) {
        int player_id = 0;  // todo : multiplayer
        int sock_fd = _player_socket_fds[player_id];

        numbytes = recv(sock_fd, buf, MAXDATASIZE - 1, 0);
        if (numbytes == -1) {
            perror("host : recv");
            continue;
        }
        buf[numbytes] = '\0';
        msg = string(buf);
        vector<string> words = split(msg, ' ');

        cerr << "host : received message \"" << msg << '\"'
             << " from player " << player_id << "\n";

        // todo : add chat messages
        if (player_id != _player_turn) {
            out = OUT_IGNORED;
        } else {
            if (words[0] == "exit") {
                cerr << "host : exiting\n";
                break;
            }
            move = _parse_input(words);
            out = _request_move(player_id, move);
        }

        numbytes = send(sock_fd, OUTCOME_STRING[out], OUTCOME_STR_MAX_LEN, 0);
        if (numbytes == -1) {
            perror("host : send");
        }
        _start_next_turn(out);
    }
}

player_move_t Host::_parse_input(const vector<string> &words) const {
    if (words.size() != 2) {
        return player_move_t(ACT_NONE, DIR_NONE);
    }

    PLAYER_ACTION action = ACT_NONE;
    DIRECTION direction = DIR_NONE;

    for (int i = 0; i < ACT_NUMBER; ++i) {
        if (words[0] == PLAYER_ACTION_STRING[i]) {
            action = (PLAYER_ACTION) i;
            break;
        }
    }

    for (int i = 0; i < DIR_NUMBER; ++i) {
        if (words[1] == DIRECTION_STRING[i]) {
            direction = (DIRECTION) i;
            break;
        }
    }

    return player_move_t(action, direction);
}

void Host::_start_next_turn(OUTCOME outcome) {
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

bool Host::_wound_other_players(int x, int y, int player_id) {
    return _gamestate->_wound_other_players(x, y, player_id);
}

OUTCOME Host::_try_shoot(int player_id, DIRECTION dir) {
    return _gamestate->_try_shoot(player_id, dir);
}

OUTCOME Host::_request_move(int player_id, player_move_t p_move) {
    return _gamestate->_request_move(player_id, p_move);
}

Host::Host() :
    _num_players(1), _max_num_players(1)
{}

Host::~Host() {
    _close_connections();
    _delete_gamesate();
}

int Host::start() {
    int ret = _start_listener();
    if (ret) {
        return ret;
    }
    return _connect_hosting_player();
}

int Host::run() {
    // todo : receive rules and game settings from hosting player

    // todo : remove nonexistent players
    cerr << "host : init gamestate\n";
    _init_gamestate();
    _player_turn = 0;

    // todo : remove when remote setup is implemented {
    cerr << "host : generate map\n";
    int ret = _gamestate->generate_map(5, 5);

    if (ret) {
        cerr << "host : failed to generate map\n";
        return 1;
    }
    cerr << "host : map generation successful\n";
    //}

    _game_loop();
    return 0;
}
