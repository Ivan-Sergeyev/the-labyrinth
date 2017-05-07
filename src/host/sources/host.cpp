#include <iostream>

#include "../headers/host.h"

#define MAXDATASIZE 100  // max number of bytes we can get at once
#define BACKLOG 10   // how many pending connections queue will hold


void _close_sock_fd(int &fd) {
    close(fd);
    fd = -1;
}

void Host::_reserve_player_sockets() {
    _player_socket_fds.reserve(_max_num_players);
}

void Host::_close_connections() {
    _close_sock_fd(_listen_sock_fd);

    for (int i = 0; i < _max_num_players; ++i) {
        if (_player_socket_fds[i] != -1) {
            _close_sock_fd(_player_socket_fds[i]);
        }
    }
}

int Host::_start_listener() {
    struct addrinfo hints, *servinfo, *p;
    int ret;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    ret = getaddrinfo(NULL, PORT, &hints, &servinfo);
    if (ret != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(ret) << '\n';
        return 1;
    }

    // loop through all the results and bind to the first we can
    int yes = 1;
    for (p = servinfo; p != NULL; p = p->ai_next) {
        _listen_sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (_listen_sock_fd == -1) {
            perror("host : socket");
            continue;
        }

        ret = setsockopt(_listen_sock_fd, SOL_SOCKET,
                         SO_REUSEADDR, &yes, sizeof(int));
        if (ret == -1) {
            perror("setsockopt");
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
    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        std::cerr << "host : failed to bind\n";
        return 1;
    }

    if (listen(_listen_sock_fd, BACKLOG) == -1) {
        perror("listen");
        return 1;
    }

    return 0;
}

int Host::_connect_hosting_player() {
    struct sigaction sa;
    sa.sa_handler = _sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
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
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            _get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        std::cerr << "host : got connection from " << s << '\n';
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
    player_move_t move;
    OUTCOME out;

    int player_id = 0;  // todo : multiplayer
    while(1) {
        int sock_fd = _player_socket_fds[player_id];
        numbytes = recv(sock_fd, buf, MAXDATASIZE - 1, 0);
        if (numbytes == -1) {
            perror("recv");
            continue;
        }
        buf[numbytes] = '\0';
        std::cerr << "host : received message \"" << buf << "\" from client\n";

        if (player_id != _player_turn) {
            out = OUT_IGNORED;
        } else {
            if (!strncmp(buf, "exit", numbytes)) {
                break;
            }
            move = _parse_input(buf, numbytes);
            out = _request_move(player_id, move);
        }

        numbytes = send(sock_fd, OUTCOME_STRING[out], OUTCOME_STR_MAX_LEN, 0);
        if (numbytes == -1) {
            perror("send");
        }
        _start_next_turn(out);
    }
}

player_move_t Host::_parse_input(const char *str, int len) const {
    PLAYER_ACTION action = ACT_NONE;
    DIRECTION direction = DIR_NONE;

    char *word1 = new char[len];
    char *word2 = new char[len];
    sscanf(str, "%s %s", word1, word2);

    for (int i = 0; i < ACT_NUMBER; ++i) {
        if (!strncmp(PLAYER_ACTION_STRING[i], word1, len)) {
            action = (PLAYER_ACTION) i;
            break;
        }
    }

    for (int i = 0; i < DIR_NUMBER; ++i) {
        if (!strncmp(DIRECTION_STRING[i], word2, len)) {
            direction = (DIRECTION) i;
            break;
        }
    }

    delete[] word1;
    delete[] word2;

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
    std::cerr << "host : init gamestate\n";
    _init_gamestate();
    _player_turn = 0;

    // todo : remove when remote setup is implemented {
    std::cerr << "host : generate map\n";
    int ret = _gamestate->generate_map(5, 5);

    if (ret) {
        std::cerr << "host : failed to generate map\n";
        return 1;
    }
    std::cerr << "host : map generation successful\n";
    //}

    _game_loop();
    return 0;
}
