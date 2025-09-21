#include "helper.h"

class DFSolver{
private:
    std::vector<node> maze;
    int x_l;
    int y_l;

    void move(coords node_c, std::vector<coords>& current_path);

public:

    DFSolver(std::vector<node> maze, int x_l, int y_l);

    void solve();

    void r_solve(int render_speed);
};