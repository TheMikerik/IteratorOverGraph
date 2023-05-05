#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>


/**
 * Statuses of the nodes were substitued by the words so its less confusing
*/
enum{
    not_visited = 0,
    processing = 1,
    visited = 2,
};


/**
 * Each node has vector<Node *> as their neighbors, ID and status
*/
struct Node{
    std::vector<Node *> neighbors;
    int id;

    int status = not_visited;
};


/**
 * Graph has nodes and it stores number of all nodes in it
*/
struct Graph{
    Node* nodes;
    int count;
};