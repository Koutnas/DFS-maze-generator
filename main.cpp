#include "DFSWorm.h"

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
    get_chart(worm.start_crawl(),x,y);
    return 0;
}
