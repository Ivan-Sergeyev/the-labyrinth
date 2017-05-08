#ifndef SRC_CLIENT_HEADERS_1_SCREEN_HOST_LOBBY_H_
#define SRC_CLIENT_HEADERS_1_SCREEN_HOST_LOBBY_H_

#include <iostream>

#include "general_screen.h"
#include "2_screen_game.h"

#include "../../host/headers/host.h"


class ScreenHostLobby : public GeneralScreen {
 private:
    void _run_host() const {
        Host host;
        if (host.start()) {
            std::cerr << "failed to start host\n";
            return;
        }
        if (host.run()) {
            std::cerr << "host error\n";
        }
    }

    int _connect_to_host() {
        int host_socket_fd;
        struct addrinfo hints, *servinfo, *p;
        int ret;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        if ((ret = getaddrinfo("localhost", PORT, &hints, &servinfo)) != 0) {
            std::cerr << "getaddrinfo: " << gai_strerror(ret) << '\n';
            return -1;
        }

        // loop through all the results and connect to the first we can
        for (p = servinfo; p != NULL; p = p->ai_next) {
            if ((host_socket_fd = socket(p->ai_family, p->ai_socktype,
                    p->ai_protocol)) == -1) {
                perror("client : socket");
                continue;
            }

            if (connect(host_socket_fd, p->ai_addr, p->ai_addrlen) == -1) {
                close(host_socket_fd);
                perror("client : connect");
                continue;
            }

            break;
        }

        if (p == NULL) {
            std::cerr << "client : failed to connect\n";
            return -2;
        }

        char s[INET6_ADDRSTRLEN];
        inet_ntop(p->ai_family, _get_in_addr((struct sockaddr *)p->ai_addr),
                s, sizeof s);
        std::cerr << "client : connecting to " << s << '\n';

        freeaddrinfo(servinfo);  // all done with this structure

        return host_socket_fd;
    }

 public:
    ScreenHostLobby() {}
    ~ScreenHostLobby() {}

    GeneralScreen* loop() {
        // todo : generate a key for host to identify hosting player
        pid_t pid = fork();
        if (pid == 0) {
            // child process is host
            _run_host();
            return nullptr;
        }

        // parent process is client

        // todo : use keys to connect to host?
        // todo : add hostname for remote connection
        int host_socket_fd = _connect_to_host();
        if (host_socket_fd < 0) {
            std::cerr << "client : failed to connect to host\n";
            return nullptr;
        }

        // todo : send rules and game settings to host
        // todo : send "start game" command to host

        ScreenGame *next_screen = new ScreenGame();
        next_screen->set_host_socket(host_socket_fd);
        return next_screen;
    }
};

#endif  // SRC_CLIENT_HEADERS_1_SCREEN_HOST_LOBBY_H_
