#include "mechanics.h"
#include <stdio.h>


int main() {
    Maze maze = {};
    create_maze(&maze);

    printf("%u\n\n", ST_WALL);

    int i = 0;
    for (i = 0; i < 10; i++) {
        ACTIONS action = get_action();
        unsigned int result = do_action(action, &maze);
        printf("%u\n", result);
//   print_result(result);
        print_maze(&maze);
    }

    return 0;
}
