#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>


#define NORMAL 0
#define POINT 1
#define PATH 3

struct coords{
    int x;
    int y;
};

struct node{
    bool visited = false;
    int modifier = NORMAL;
    bool up = true;
    bool down = true;
    bool right = true;
    bool left = true;
};

struct family{
    coords parent;
    coords child;
};

void get_chart(std::vector<node> maze, int x, int y);

bool compare_coords(coords c1, coords c2);

coords find_start(std::vector<node> maze,int x_l, int y_l);
