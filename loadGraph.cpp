#include "loadGraph.h"

int GetLines(std::string filename){
    std::ifstream inputFile(filename); 
    int numLines = 0;
    std::string line;

    while (getline(inputFile, line)){
        numLines++;
    }

    inputFile.close();
    return numLines;
}


int GetNodeCount(std::string filename){
    int from, to;
    std::vector<int> isPart;
    int lines = GetLines(filename);

    bool checkFrom = false;
    bool checkTo = false;
    std::ifstream infile(filename);
    for(int i=0; i<lines; i++){
        infile >> from >> to;
        
        for (std::vector<int>::size_type j=0; j<isPart.size(); j++){
            if ( isPart[j] == from ){
                checkFrom = true;
            }
            if ( isPart[j] == to ){
                checkTo = true;
            }
        }
        if (checkFrom == false){
            isPart.push_back(from);
        }
        if (checkTo == false){
            isPart.push_back(to);
        }

        checkFrom = false;
        checkTo = false;
    }
    
    infile.close();
    return isPart.size();
}


Graph loadGraph(std::string filename){
        int from, to;
    std::ifstream infile(filename);

    if(!infile.is_open()){
        std::cerr << "Graph cannot be loaded" << std::endl;
        exit(-1);
    }

    int count = GetNodeCount(filename);
    Node* nodes = new Node[count];
    Graph graph = {nodes, count};

    for (int i = 0; i < count; i++) {
        nodes[i].id = i;
    }
    for (int i=0; !infile.eof(); i++){
        infile >> from >> to;
        if (!infile.fail()) {
            nodes[from].neighbors.push_back(nodes + to);
            nodes[to].neighbors.push_back(nodes + from);
        }
    }
    infile.close();	
    return graph;
}


void printGraph(Graph graph){
    std::cout << "Lets print each node and its neighbors:" << std::endl;
	for (int i=0; i<graph.count; i++){
        
		std::cout << "     Node " << graph.nodes[i].id << ": ";
		for (Node *x:graph.nodes[i].neighbors){
			std::cout<< x->id << " ";
		}
		std::cout << std::endl;
	}
}