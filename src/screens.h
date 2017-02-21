#ifndef SRC_SCREENS_H_
#define SRC_SCREENS_H_

enum SCREEN_ID {SC_EXIT = -1, SC_TITLE, SC_NUM_SCREENS};

#include "0_screen_main_menu.h"

SCREEN_ID (* const screens[SC_NUM_SCREENS])() = {main_menu};

#endif  // SRC_SCREENS_H_
