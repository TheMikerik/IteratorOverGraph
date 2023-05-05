#pragma once

#include "graph.h"


/**
 * Count number of lines in file on input.
 * 
 * @param filename Path to the input file
 * @return Number of lines in selected file
*/
int GetLines(std::string filename);


/**
 * Calculation of all original nodes in the graph.
 * 
 * @param filename Path to the input file
 * @return Number of original nodes in graph
*/
int GetNodeCount(std::string filename);


/**
 * It loads all nodes and its neighborows from the input file.
 * 
 * @param filename Path to the input file
 * @return Graph of the nodes and its neighborows
 * 
 * This part of the code was provided to me by mr. Kot in CV5.
 * However it is slightly modified for this exact project.
*/
Graph loadGraph(std::string filename);


/**
 * This prints the raw graph starting from the first node based on loading.
 * Prints each node and its neighborows.
 * 
 * @param graph Graph that should be printed
 * 
 * This part of the code was provided to me by mr. Kot in CV5.
 * However it is slightly modified for this exact project.
*/
void printGraph(Graph graph);