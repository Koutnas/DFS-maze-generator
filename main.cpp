#include "DFSWorm.h"
#include "BFSolver.h"
#include "DFSolver.h"


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
    //worm.render_crawl();
    maze = worm.start_crawl();
    get_chart(maze,x,y);
    DFSolver solver = DFSolver(maze,x,y);
    solver.solve();
    return 0;
}
