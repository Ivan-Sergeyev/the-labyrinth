#include "../headers/app.h"
#include "../headers/0_screen_main_menu.h"


int main() {
    ScreenMainMenu *main_menu = new ScreenMainMenu();
    return App(main_menu).run();
    delete main_menu;
}
