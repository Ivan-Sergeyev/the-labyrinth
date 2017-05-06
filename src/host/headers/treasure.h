#ifndef SRC_HOST_HEADERS_TREASURE_H_
#define SRC_HOST_HEADERS_TREASURE_H_

class Treasure {
 private:
    int _x_pos, _y_pos;
    bool _is_fake;

 public:
    Treasure();

    void set_fake(bool fake = true);

    void set_pos(int x, int y);
};

#endif  // SRC_HOST_HEADERS_TREASURE_H_
