#include "graph.h"
#include "loadGraph.h"
#include "iterator.cpp"

int main(){
    for (int in=1; in<8; in++){
        std::string path = "./Graphs/Graph" + std::to_string(in) + ".txt";

        Graph graph = loadGraph(path);
        Iterator dfs(graph);
        std::cout << "Graph" << in << " has " << graph.count << " original nodes." << std::endl;
        printGraph(graph);

        dfs.Reset(graph);   
        dfs.PrintInfo();
        dfs.DoDFS();

        graph = loadGraph(path);
        Iterator bfs(graph);
        dfs.DoBFS();

        std::cout << "\n\n\n\n";
    }

    std::cout << "This is the very end.\n\n" << std::endl;
    return 0;
}