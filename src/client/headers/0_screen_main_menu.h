#ifndef SRC_CLIENT_HEADERS_0_SCREEN_MAIN_MENU_H_
#define SRC_CLIENT_HEADERS_0_SCREEN_MAIN_MENU_H_

#include "general_screen.h"
#include "1_screen_host_lobby.h"


class ScreenMainMenu : public GeneralScreen {
 private:
    enum MAIN_MENU_BUTTONS {
        MM_NEW_GAME = 0, MM_EXIT, MM_NUM_BUTTONS
    };
    const char* const MENU_OPTIONS[MM_NUM_BUTTONS] = {"New Game", "Exit"};

    void draw_menu(int highlight) {
        int height, width;
        getmaxyx(stdscr, height, width);

        int x = (width - MM_NUM_BUTTONS) / 2;
        int y = height / 2;

        for (int i = 0; i < MM_NUM_BUTTONS; ++i) {
            if (i == highlight) {
                attron(A_REVERSE);
                mvprintw(y, x, MENU_OPTIONS[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(y, x, MENU_OPTIONS[i]);
            }
            ++y;
        }
        refresh();
    }

 public:
    ScreenMainMenu() {}
    ~ScreenMainMenu() {}

    GeneralScreen* loop(Gamestate **gamestate) {
        // todo : change argument from gamestate to host sockfd
        GeneralScreen *next_screen;

        noecho();

        int key = 0;
        bool exit = false;
        int highlight = 0;

        while (1) {
            draw_menu(highlight);

            key = getch();
            switch (key) {
            case 27:  // escape
                exit = true;
                break;
            case KEY_ENTER:
            case 13:
            case 10:  // enter
                switch (highlight) {
                    case MM_NEW_GAME:
                        next_screen = new ScreenHostLobby();
                        return next_screen;
                    case MM_EXIT:
                        exit = true;
                        break;
                }
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % MM_NUM_BUTTONS;
                break;
            case KEY_UP:
                highlight = (MM_NUM_BUTTONS + highlight - 1) % MM_NUM_BUTTONS;
                break;
            }

            if (exit) {
                return nullptr;
            }
        }
    }
};

#endif  // SRC_CLIENT_HEADERS_0_SCREEN_MAIN_MENU_H_
