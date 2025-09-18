#include <vector>
#include <cstdlib>
#include <iostream>

struct coords{
    int x;
    int y;
};

struct node{
    bool visited = false;
    bool up = true;
    bool down = true;
    bool right = true;
    bool left = true;
};

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