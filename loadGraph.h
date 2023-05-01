#pragma once

#include "graph.h"

int GetLines(std::string filename);
int GetNodeCount(std::string filename);
Graph loadGraph(std::string filename);
void printGraph(Graph graph);