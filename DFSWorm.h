#include "helper.h"


class DFSWorm{
private:
    std::vector<node> maze;
    int purity = 100; //int somewhere betwen 0-100 representing percentage of how many nodes will have some extra wall removed; 100 by deafult - generating mathematically perfect maze
    int x_l;
    int y_l;
    int x;
    int y;

    bool avalible(int xl, int yl);

    std::vector<int> validate_moves();

    int pick_move(std::vector<int> moves);

    void move(int moveint);

    void delete_wall(std::vector<int> &valid_walls,int rx, int ry);

    void taint_maze();

public:

    DFSWorm(int x_l, int y_l);

    std::vector<node> start_crawl();

    void render_crawl();

    void set_purity(int purity);

};