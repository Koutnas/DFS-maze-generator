#include "DFSWorm.h"
#include <queue>

void get_chart(std::vector<node> chart,int x,int y){
    int chart_i = 0;
    for(int a = 0; a < x; a++){std::cout<<"+---";}std::cout<<"+"; //tiskne prvni radek

    for(int i = 0; i < 2*y; i++){
        std::cout<<"\n";
        switch (i%2)
            {
            case 1:
                if((i != (2*y)-1)){
                    for(int j = 0; j < x; j++){
                        if(!chart[j + x*chart_i].down && !chart[j + x*(chart_i+1)].up){std::cout<<"+   ";}
                        else{std::cout<<"+---";}
                    }
                    std::cout<<"+";
                }
                break;
            case 0:
                if(chart[chart_i*x].modifier == POINT){
                    std::cout<<"| ⚑ ";
                }else if(chart[chart_i*x].modifier == PATH){
                    std::cout<<"|\033[32m ■ \033[0m";
                }else{
                    std::cout<<"|   ";}
                for(int j = 0; j < x-1; j++){
                    switch(chart[j + x*chart_i+1].modifier){ //eventough the cell physically exists in the space it only renders the cell after
                        case NORMAL:
                            if(!chart[j + x*chart_i].right && !chart[j+1 + x*chart_i].left){std::cout<<"    ";}
                            else{std::cout<<"|   ";}
                            break;
                        case POINT:
                            if(!chart[j + x*chart_i].right && !chart[j+1 + x*chart_i].left){std::cout<<" ⚑  ";}
                            else{std::cout<<"| ⚑ ";}
                            break;
                        case PATH:
                            if(!chart[j + x*chart_i].right && !chart[j+1 + x*chart_i].left){std::cout<<"\033[32m  ■ \033[0m";}
                            else{std::cout<<"|\033[32m ■ \033[0m";}
                            break;
                    }
                }
                std::cout<<"|";
                break;
            }
        if((i+1)%2 == 0){chart_i += 1;} //Check so that all cells are called aproprietly chart_i is something that replaces function "i//2"
    }

    for(int a = 0; a < x; a++){std::cout<<"+---";}std::cout<<"+";
}

class BFSolver{
public:
    int x_l;
    int y_l;
    std::vector<node> maze;

    BFSolver(std::vector<node> maze, int x_l ,int y_l){
        this->maze = maze;
        this->x_l = x_l;
        this->y_l = y_l;
    }
    coords find_start(){
        coords start;
        start.x = 0; start.y = 0;
        for(int i = 0;i<x_l*y_l;i++){
            if(maze[i].modifier == POINT){
                start.x = i%x_l;
                start.y = (i-start.x)/x_l;
                return start;
            }
        }
        return start;
    }
    bool compare_coords(coords c1, coords c2){
        if (c1.x == c2.x && c1.y == c2.y){
            return true;
        }
        else{
            return false;
        }
    }
    void add_neighbours(coords node_c,std::queue<coords>& q, std::vector<family>& registry){ //passing by address - thus directly modifying original vector and q
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

    void markdown_solution(std::vector<family> &registry,coords start,coords end){
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


    void solve(){
        coords end;
        coords start = find_start();
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


};

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
    get_chart(maze,x,y);
    BFSolver solver = BFSolver(maze,x,y);
    solver.solve();
    return 0;
}
