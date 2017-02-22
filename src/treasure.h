#ifndef SRC_TREASURE_H_
#define SRC_TREASURE_H_

class Treasure {
 private:
    int _is_fake;
    int _x_pos, _y_pos;

 public:
    Treasure() : _x_pos(0), _y_pos(0), _is_fake(false) {}


    void set_fake(int fake = true) {
        _is_fake = fake;
    }

    void set_pos(int x, int y) {
        _x_pos = x;
        _y_pos = y;
    }
};

#endif  // SRC_TREASURE_H_
