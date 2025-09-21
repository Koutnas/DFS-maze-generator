#include "DFSWorm.h"


DFSWorm::DFSWorm(int x_l,int y_l){
    this->x_l = x_l;
    this->y_l = y_l;
    for(int i = 0; i < x_l*y_l; i++){
        node tmp;
        maze.push_back(tmp);
    }
    std::srand(time(NULL));
    int r1 = rand()%(x_l*y_l);
    int r2 = rand()%(x_l*y_l);
    maze[r1].modifier = POINT;
    maze[r2].modifier = POINT; //setting start and end for a maze
}

bool DFSWorm::avalible(int xl,int yl){
    if(xl < 0 || xl >= x_l || yl < 0 || yl >= y_l){
            return false;
        }
        if(maze[xl + x_l*yl].visited){
            return false;
        }
        return true;
}

std::vector<int> DFSWorm::validate_moves(){
        std::vector<int> positions;
        if(avalible(x,y-1)){positions.push_back(1);} //std::cout<<"up passed"<<std::endl;}//UP
        if(avalible(x+1,y)){positions.push_back(2);} //std::cout<<"right passed"<<std::endl;}//RIGHT
        if(avalible(x,y+1)){positions.push_back(3);} //std::cout<<"down passed"<<std::endl;}//DOWN
        if(avalible(x-1,y)){positions.push_back(4);} //std::cout<<"left passed"<<std::endl;}//LEFT

        return positions;
}

int DFSWorm::pick_move(std::vector<int> moves){
    return moves[std::rand()%moves.size()];
}

void DFSWorm::move(int moveint){
    switch(moveint){
            case 1:
                maze[x + x_l*y].up = false;
                maze[x + x_l*(y-1)].down = false;
                maze[x + x_l*(y-1)].visited = true;
                y -= 1;
                break;
            case 2:
                maze[x + x_l*y].right = false;
                maze[x+1 + x_l*y].left = false;
                maze[x+1 + x_l*y].visited = true;
                x += 1;
                break;
            case 3:
                maze[x + x_l*y].down = false;
                maze[x + x_l*(y+1)].up = false;
                maze[x + x_l*(y+1)].visited = true;
                y += 1;
                break;
            case 4:
                maze[x + x_l*y].left = false;
                maze[x-1 + x_l*y].right = false;
                maze[x-1 + x_l*y].visited = true;
                x -= 1;
                break;
        }
}
void DFSWorm::delete_wall(std::vector<int> &walls,int rx, int ry){
    std::vector<int> lotto;
    node curr = maze[rx + x_l*ry];
    if(rx == 0){
        walls[3] = 0;
    }
    else if(rx == x_l -1){
        walls[1] = 0;
    }

    if(ry == 0){
        walls[0] = 0;
    }
    else if(ry == y_l-1){
        walls[2] = 0; 
    }

    if(!curr.up){walls[0] = 0;}
    if(!curr.right){walls[1] = 0;}
    if(!curr.down){walls[2] = 0;}
    if(!curr.left){walls[3] = 0;}

    for(int i = 0; i < 4;i++){
        if(walls[i] > 0){
            lotto.push_back(walls[i]);
        }
    }
    if(lotto.empty()){return;}

    switch(lotto[rand()%lotto.size()]){
        case 1:
            maze[rx + x_l*ry].up = false;
            maze[rx + x_l*(ry-1)].down = false;
            break;
        case 2:
            maze[rx + x_l*ry].right = false;
            maze[rx+1 + x_l*ry].left = false;
            break;
        case 3:
            maze[rx + x_l*ry].down = false;
            maze[rx + x_l*(ry+1)].up = false;
            break;
        case 4:
            maze[rx + x_l*ry].left = false;
            maze[rx-1 + x_l*ry].right = false;
            break;
    }
}

void DFSWorm::taint_maze(){
    if(purity == 100){return;}
    

    int node_count = (x_l*y_l)*((100-purity)/100.0);
    int rx;
    int ry;

    for(int i = 0; i < node_count; i++){
        rx = rand()%x_l;
        ry = rand()%y_l;
        std::vector<int> valid_walls = {1,2,3,4};
        delete_wall(valid_walls,rx,ry);
    }
}

std::vector<node> DFSWorm::start_crawl(){
        int moveint;
        std::vector<coords> stack;
        this->x = std::rand()%x_l;
        this->y = std::rand()%y_l; //start at random position
        maze[x + x_l*y].visited = true;
        //std::cout<<"Starteted at: "<<x<<","<<y<<std::endl;

        while (true)
        {   
            std::vector<int> moves = validate_moves();
            if(moves.size() == 0 && stack.size() == 0){break;}
            coords now;
            now.x = x;
            now.y = y;
            stack.push_back(now);

            if(moves.size() == 0){
                stack.pop_back();
                x = stack.back().x;
                y = stack.back().y;
                stack.pop_back();
                continue;
                }
            moveint = pick_move(moves);
            move(moveint);
            //std::cout<<"\n";
            //get_chart(maze,x_l,y_l);
            //std::cout<<"stepped to: "<<x<<","<<y<<std::endl; //For debugging
        }
        for(int i = 0; i < x_l*y_l; i++){maze[i].visited = false;} // Useless change but helps with readability if maze is processed further
        taint_maze();
        return maze;
}

void DFSWorm::render_crawl(){
        std::cout << "\033[2J\033[1;1H";
        int moveint;
        std::vector<coords> stack;
        this->x = std::rand()%x_l;
        this->y = std::rand()%y_l; //start at random position
        maze[x + x_l*y].visited = true;
        //std::cout<<"Starteted at: "<<x<<","<<y<<std::endl;

        while (true)
        {   
            std::vector<int> moves = validate_moves();
            if(moves.size() == 0 && stack.size() == 0){break;}
            coords now;
            now.x = x;
            now.y = y;
            stack.push_back(now);

            if(moves.size() == 0){
                stack.pop_back();
                x = stack.back().x;
                y = stack.back().y;
                stack.pop_back();
                continue;
                }
            moveint = pick_move(moves);
            move(moveint);
            get_chart(maze,x_l,y_l);
            std::this_thread::sleep_for(std::chrono::milliseconds(75));
        }
}

void DFSWorm::set_purity(int purity){
    if(purity>=0 && purity<=100){
        this->purity = purity;
    }
}