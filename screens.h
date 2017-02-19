#ifndef SCREENS_H_
#define SCREENS_H_

enum SCREEN_ID {SC_EXIT = -1, SC_TITLE, num_screens};

#include "title_screen.h"

SCREEN_ID (* const screens[num_screens])() = {title_screen};

#endif  // SCREENS_H_
