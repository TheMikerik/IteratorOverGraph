#include "graph.h"
#include "loadGraph.h"
#include "loadGraph.cpp"
#include "DFSIterator.h"
#include "DFSIterator.cpp"
#include "BFSIterator.h"
#include "BFSIterator.cpp"


int main(){
    for (int in=1; in<8; in++){
        std::string path = "./Graphs/Graph" + std::to_string(in) + ".txt";
        std::cout << "\nGraph " << in << ":\n";
        DFSIterator iterDFS(loadGraph(path));
        BFSIterator iterBFS(loadGraph(path));

        std::cout << "     DFS: ";
        for( iterDFS.Reset(); !iterDFS.IsEnd(); iterDFS.Next()){
            std::cout << iterDFS.CurrentKey() << " ";
        }

        std::cout << "\n     BFS: ";
        for( iterBFS.Reset(); !iterBFS.IsEnd(); iterBFS.Next()){
            std::cout << iterBFS.CurrentKey() << " ";
        }
    }
}