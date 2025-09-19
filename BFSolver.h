#include "helper.h"
#include <queue>

class BFSolver{

private:
    int x_l;
    int y_l;
    std::vector<node> maze;
    
    coords find_start();

    bool compare_coords(coords c1, coords c2);

    void add_neighbours(coords node_c, std::queue<coords> &q, std::vector<family> &registry);

    void markdown_solution(std::vector<family> &registry, coords start, coords end);

public:
    BFSolver(std::vector<node> maze, int x_l, int y_l);

    void solve();
};
