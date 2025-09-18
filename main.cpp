#include <iostream>
#include <cstdlib>
#include <vector>

struct coords{
    int x;
    int y;
};

struct node{
    bool visited = false;
    bool up = true;
    bool down = true;
    bool right = true;
    bool left = true;
};

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
                std::cout<<"|   ";
                for(int j = 0; j < x-1; j++){
                    if(!chart[j + x*chart_i].right && !chart[j+1 + x*chart_i].left){std::cout<<"    ";}
                    else{std::cout<<"|   ";}
                }
                std::cout<<"|";
                break;
            }
        if((i+1)%2 == 0){chart_i += 1;} //Check so that all cells are called aproprietly chart_i is something that replaces function "i//2"
    }

    for(int a = 0; a < x; a++){std::cout<<"+---";}std::cout<<"+";

}

class DFSWorm{
public:
    std::vector<node> maze;
    int x_l;
    int y_l;
    int x;
    int y;

    DFSWorm(int x_l, int y_l){
        this->x_l = x_l;
        this->y_l = y_l;
        for(int i = 0; i < x_l*y_l; i++){
            node tmp;
            maze.push_back(tmp);
        }
    }


    bool avalible(int xl, int yl){
        if(xl < 0 || xl >= x_l || yl < 0 || yl >= y_l){
            return false;
        }
        if(maze[xl + x_l*yl].visited){
            return false;
        }
        return true;
    }

    std::vector<int> validate_moves(){
        std::vector<int> positions;
        if(avalible(x,y-1)){positions.push_back(1);} //std::cout<<"up passed"<<std::endl;}//UP
        if(avalible(x+1,y)){positions.push_back(2);} //std::cout<<"right passed"<<std::endl;}//RIGHT
        if(avalible(x,y+1)){positions.push_back(3);} //std::cout<<"down passed"<<std::endl;}//DOWN
        if(avalible(x-1,y)){positions.push_back(4);} //std::cout<<"left passed"<<std::endl;}//LEFT

        return positions;
    }

    int pick_move(std::vector<int> moves){
        return moves[std::rand()%moves.size()];
    }

    void move(int moveint){
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

    void start_crawl(){
        std::srand(time(NULL));
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
            //std::cout<<"stepped to: "<<x<<","<<y<<std::endl;
        }
        
        get_chart(maze,x_l,y_l);
        std::cout<<"\n";
    }

};

int main(){
    /*
    DFSWorm worm = DFSWorm();
    worm.start_crawl();
    return 0;
    
    std::vector<node> maze;
    int y_l = 5;
    int x_l = 5;
    for(int i = 0; i < x_l*y_l; i++){
        node tmp;
        maze.push_back(tmp);
    }
    maze[16].down = false;
    maze[21].up = false;
    get_chart(maze,x_l,y_l);
    */

    
    int x;
    int y;
    std::vector<node> maze;
    std::cin>>x;
    std::cout<<std::endl;
    std::cin>>y;
    DFSWorm worm = DFSWorm(x,y);
    worm.start_crawl();


}
