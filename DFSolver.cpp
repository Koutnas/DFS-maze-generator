#include "DFSolver.h"

DFSolver::DFSolver(std::vector<node> maze,int x_l, int y_l){
    this->maze = maze;
    this->x_l = x_l;
    this->y_l = y_l;
}

void DFSolver::move(coords node_c,std::vector<coords> &current_path){
    node current = maze[node_c.x + x_l*node_c.y];
        
    if(!current.up && !maze[node_c.x + x_l*(node_c.y-1)].visited){
        coords tmp; tmp.x = node_c.x; tmp.y = node_c.y-1;
        maze[tmp.x + x_l*tmp.y].visited = true;
        current_path.push_back(tmp);
    }
    else if(!current.right && !maze[node_c.x+1 + x_l*(node_c.y)].visited){
        coords tmp; tmp.x = node_c.x+1; tmp.y = node_c.y;
        maze[tmp.x + x_l*tmp.y].visited = true;
        current_path.push_back(tmp);
    }
    else if(!current.down && !maze[node_c.x + x_l*(node_c.y+1)].visited){
        coords tmp; tmp.x = node_c.x; tmp.y = node_c.y+1;
        maze[tmp.x + x_l*tmp.y].visited = true;
        current_path.push_back(tmp);
    }
    else if(!current.left && !maze[node_c.x-1 + x_l*(node_c.y)].visited){
        coords tmp; tmp.x = node_c.x-1; tmp.y = node_c.y;
        maze[tmp.x + x_l*tmp.y].visited = true;
        current_path.push_back(tmp);
    }
    else{
        current_path.pop_back();
    }
}

void DFSolver::solve(){
    coords end;
    coords start = find_start(maze,x_l,y_l);
    maze[start.x + start.y*x_l].visited = true;
    std::vector<coords> current_path;
    current_path.push_back(start);
    while(compare_coords(start,current_path.back()) || maze[current_path.back().x + current_path.back().y*x_l].modifier != POINT) {
        move(current_path.back(),current_path);
    }
    /*
    for(int i = 0; i < current_path.size(); i++){
        std::cout<<"\n step: "<<current_path[i].x<<","<<current_path[i].y;
    }
    */
    for(int i = 0; i < current_path.size(); i++){
        if(maze[current_path[i].x + x_l*current_path[i].y].modifier != POINT){
            maze[current_path[i].x + x_l*current_path[i].y].modifier = PATH;
        }
    }
    std::cout<<"\n";
    get_chart(maze,x_l,y_l);

}
