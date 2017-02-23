#ifndef SRC_GRAPHICS_HEADERS_SCREENS_H_
#define SRC_GRAPHICS_HEADERS_SCREENS_H_

#include <ncurses.h>


enum SCREEN_ID {SC_EXIT = -1, SC_MAIN_MENU, SC_GAME, SC_NUM_SCREENS};

#define SC_FIRST SC_MAIN_MENU

#include "0_screen_main_menu.h"
#include "1_screen_game.h"

SCREEN_ID (* const screens[SC_NUM_SCREENS])() = {main_menu, game};

#endif  // SRC_GRAPHICS_HEADERS_SCREENS_H_
