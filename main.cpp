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
    worm.set_purity(50);
    maze = worm.start_crawl();
    get_chart(maze,x,y);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    DFSolver dsolver = DFSolver(maze,x,y);
    dsolver.r_solve(75);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    BFSolver bsolver = BFSolver(maze,x,y);
    bsolver.r_solve();
    return 0;
}
