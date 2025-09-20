#include "BFSolver.h"

BFSolver::BFSolver(std::vector<node> maze, int x_l ,int y_l){
        this->maze = maze;
        this->x_l = x_l;
        this->y_l = y_l;
    }


void BFSolver::add_neighbours(coords node_c,std::queue<coords>& q, std::vector<family>& registry){ //passing by address - thus directly modifying original vector and q
    coords tmpc;
    family tmpf;
    node curr = maze[node_c.x + x_l*node_c.y];
    //std::cout<<node_c.x<<","<<node_c.y<<std::endl;

    if(!curr.up && !maze[node_c.x + x_l*(node_c.y-1)].visited){ // searches for holes and if it was visited UP
        tmpc.x = node_c.x; tmpc.y = node_c.y - 1;
        maze[tmpc.x + x_l*tmpc.y].visited = true;
        q.push(tmpc);
        tmpf.parent = node_c; tmpf.child = tmpc;
        registry.push_back(tmpf);
    }

    if(!curr.right && !maze[node_c.x+1 + x_l*(node_c.y)].visited){ // searches for holes and if it was visited RIGHT
        tmpc.x = node_c.x+1; tmpc.y = node_c.y;
        maze[tmpc.x + x_l*tmpc.y].visited = true;
        q.push(tmpc);
        tmpf.parent = node_c; tmpf.child = tmpc;
        registry.push_back(tmpf);
    }

    if(!curr.down && !maze[node_c.x + x_l*(node_c.y+1)].visited){ // searches for holes and if it was visited DOWN
        tmpc.x = node_c.x; tmpc.y = node_c.y+1;
        maze[tmpc.x + x_l*tmpc.y].visited = true;
        q.push(tmpc);
        tmpf; tmpf.parent = node_c; tmpf.child = tmpc;
        registry.push_back(tmpf);
    }

    if(!curr.left && !maze[node_c.x-1 + x_l*(node_c.y)].visited){ // searches for holes and if it was visited LEFT
        tmpc.x = node_c.x-1; tmpc.y = node_c.y;
        maze[tmpc.x + x_l*tmpc.y].visited = true;
        q.push(tmpc);
        tmpf; tmpf.parent = node_c; tmpf.child = tmpc;
        registry.push_back(tmpf);
    }
}

void BFSolver::markdown_solution(std::vector<family> &registry,coords start,coords end){
    coords current = end;
    while(!compare_coords(current,start)){
        
        for(int i = 0; i < registry.size(); i++){
            if(compare_coords(registry[i].child,current)){
                current = registry[i].parent;
                if(maze[current.x + x_l*current.y].modifier != POINT){
                    maze[current.x + x_l*current.y].modifier = PATH;
                }
            }
        }
    }
    std::cout<<std::endl;
    get_chart(maze,x_l,y_l);
}

void BFSolver::solve(){
    coords end;
    coords start = find_start(maze,x_l,y_l);
    std::queue<coords> q;
    std::vector<family> registry;
    maze[start.x + x_l*start.y].visited = true;
    q.push(start);
    while(compare_coords(q.front(),start) || maze[q.front().x + x_l*q.front().y].modifier != POINT && !q.empty()){
        add_neighbours(q.front(),q,registry);
        q.pop();
    }
    end = q.front();
    /*for(int i = 0; i < registry.size(); i++){
        std::cout<<"\n parent: "<<registry[i].parent.x<<","<<registry[i].parent.y<<"\tchild: "<<registry[i].child.x<<","<<registry[i].child.y<<std::endl;
    }*/
    markdown_solution(registry,start,end);
}