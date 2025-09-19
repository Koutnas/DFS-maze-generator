#include <vector>
#include <cstdlib>
#include <iostream>
#include "struct.h"


class DFSWorm{
private:
    std::vector<node> maze;
    int x_l;
    int y_l;
    int x;
    int y;

    bool avalible(int xl, int yl);

    std::vector<int> validate_moves();

    int pick_move(std::vector<int> moves);

    void move(int moveint);

public:

    DFSWorm(int x_l, int y_l);

    std::vector<node> start_crawl();

};