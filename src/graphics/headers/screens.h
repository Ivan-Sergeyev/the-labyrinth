#ifndef SRC_GRAPHICS_HEADERS_SCREENS_H_
#define SRC_GRAPHICS_HEADERS_SCREENS_H_

#include <ncurses.h>


enum SCREEN_ID {
    SCR_EXIT = -1,
    SCR_MAIN_MENU, SCR_LOBBY, SCR_GAME,
    SCR_NUM_SCREENS
};

#define SCR_FIRST SCR_MAIN_MENU

#include "0_screen_main_menu.h"
#include "1_screen_lobby.h"
#include "2_screen_game.h"

SCREEN_ID (* const screens[SCR_NUM_SCREENS])(Gamestate *) = {
    main_menu, lobby, game
};

#endif  // SRC_GRAPHICS_HEADERS_SCREENS_H_
