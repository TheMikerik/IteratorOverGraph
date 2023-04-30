#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

enum{
    UNCHECKED = 0,
    CHECKING = 1,
    CHECKED = 2,
};

struct Node{
    std::vector<Node *> neighbors;
    int id;

    int status = UNCHECKED;
};

struct Graph{
    Node* nodes;
    int count;
};