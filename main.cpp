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
    worm.set_purity(0);
    maze = worm.start_crawl();
    get_chart(maze,x,y);
    DFSolver dsolver = DFSolver(maze,x,y);
    dsolver.solve();
    BFSolver bsolver = BFSolver(maze,x,y);
    bsolver.solve();
    return 0;
}
