#ifndef SRC_CLIENT_HEADERS_SCREENS_H_
#define SRC_CLIENT_HEADERS_SCREENS_H_

#include <ncurses.h>


enum SCREEN_ID {
    SCR_EXIT = -1,
    SCR_MAIN_MENU, SCR_LOBBY, SCR_GAME,
    SCR_NUMBER
};

#define SCR_FIRST SCR_MAIN_MENU

#include "0_screen_main_menu.h"
#include "1_screen_host_lobby.h"
#include "2_screen_game.h"

// todo : change argument from gamestate to host sockfd
SCREEN_ID (* const screens[SCR_NUMBER])(Gamestate **) = {
    main_menu, host_lobby, game
};

#endif  // SRC_CLIENT_HEADERS_SCREENS_H_
