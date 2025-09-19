#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>

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