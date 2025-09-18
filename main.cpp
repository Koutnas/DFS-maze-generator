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

void get_chart(node chart[][5],int x,int y){
    int chart_i = 0;
    for(int a = 0; a < x; a++){std::cout<<"+---";}std::cout<<"+"; //tiskne prvni radek

    for(int i = 0; i < 2*y; i++){
        std::cout<<"\n";
        switch (i%2)
            {
            case 1:
                if((i != (2*y)-1)){
                    for(int j = 0; j < x; j++){
                        if(!chart[chart_i][j].down && !chart[chart_i+1][j].up){std::cout<<"+   ";}
                        else{std::cout<<"+---";}
                    }
                    std::cout<<"+";
                }
                break;
            case 0:
                std::cout<<"|   ";
                for(int j = 0; j < x-1; j++){
                    if(!chart[chart_i][j].right && !chart[chart_i][j+1].left){std::cout<<"    ";}
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
    node maze[5][5];
    int x_l = 5;
    int y_l = 5;
    int x;
    int y;


    bool avalible(int xl, int yl){
        if(xl < 0 || xl >= x_l || yl < 0 || yl >= y_l){
            return false;
        }
        if(maze[yl][xl].visited){
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
                maze[y][x].up = false;
                maze[y-1][x].down = false;
                maze[y-1][x].visited = true;
                y -= 1;
                break;
            case 2:
                maze[y][x].right = false;
                maze[y][x+1].left = false;
                maze[y][x+1].visited = true;
                x += 1;
                break;
            case 3:
                maze[y][x].down = false;
                maze[y+1][x].up = false;
                maze[y+1][x].visited = true;
                y += 1;
                break;
            case 4:
                maze[y][x].left = false;
                maze[y][x-1].right = false;
                maze[y][x-1].visited = true;
                x -= 1;
                break;
        }
    }

    void recursive_movement(){
        std::vector<coords> stack;
        coords now;
        now.x = x;
        now.y = y;
        stack.push_back(now);
        std::vector<int> moves = validate_moves();

        if(moves.size() == 0){
            stack.pop_back();
            x = stack.back().x;
            y = stack.back().y;
            stack.pop_back();
            }
        int moveint = pick_move(moves);
        move(moveint);
        std::cout<<"\n";
        get_chart(maze,5,5);
        std::cout<<"stepped to: "<<x<<","<<y<<std::endl;
    }


    void start_crawl(){
        std::srand(23);
        int moveint;
        std::vector<coords> stack;
        this->x = std::rand()%x_l;
        this->y = std::rand()%y_l; //start at random position
        maze[y][x].visited = true;
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
            //get_chart(maze,5,5);
            //std::cout<<"stepped to: "<<x<<","<<y<<std::endl;
        }
        
        get_chart(maze,5,5);
        std::cout<<"\n";
    }

};

int main(){
    DFSWorm worm = DFSWorm();
    worm.start_crawl();
    return 0;
    //
    //node maze[5][5];
    //maze[1][3].right = false;
    //maze[1][4].left = false;
    //maze[1][4].visited = true;
    //maze[3][3].left = false;
    //maze[3][2].right = false;
    //get_chart(maze,5,5);
    

}
