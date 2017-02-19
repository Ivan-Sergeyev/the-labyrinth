#ifndef SRC_TREASURE_H_
#define SRC_TREASURE_H_

class Treasure {
 private:
    int is_fake;
    int x_pos, y_pos;

 public:
    Treasure(int x, int y, int fake = 0) : x_pos(x), y_pos(y), is_fake(fake) {}

    void move(int new_x, int new_y) {
        x_pos = new_x;
        y_pos = new_y;
    }
};

#endif  // SRC_TREASURE_H_
