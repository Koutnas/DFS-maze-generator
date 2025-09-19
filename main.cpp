#include "DFSWorm.h"
#include "BFSolver.h"
#include <queue>


int main(){

    int x;
    int y;
    std::vector<node> maze;
    std::cout<<"x:";
    std::cin>>x;
    std::cout<<std::endl;
    std::cout<<"y:";
    std::cin>>y;
    DFSWorm worm = DFSWorm(x,y);
    maze = worm.start_crawl();
    //get_chart(maze,x,y);
    BFSolver solver = BFSolver(maze,x,y);
    solver.solve();
    return 0;
}
