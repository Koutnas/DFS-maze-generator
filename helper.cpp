#include "helper.h"

void get_chart(std::vector<node> chart,int x, int y){
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
                    std::cout<<"|\033[32m • \033[0m";
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
                            if(!chart[j + x*chart_i].right && !chart[j+1 + x*chart_i].left){std::cout<<"\033[32m  • \033[0m";}
                            else{std::cout<<"|\033[32m • \033[0m";}
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