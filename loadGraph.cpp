#include "loadGraph.h"


/**
 * Count number of lines in file on input.
 * 
 * @param filename Path to the input file
 * @return Number of lines in selected file
*/
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


/**
 * Calculation of all original nodes in the graph.
 * 
 * @param filename Path to the input file
 * @return Number of original nodes in graph
*/
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


/**
 * It loads all nodes and its neighborows from the input file.
 * 
 * @param filename Path to the input file
 * @return Graph of the nodes and its neighborows
 * 
 * This part of the code was provided to me by mr. Kot in CV5.
 * However it is slightly modified for this exact project.
*/
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


/**
 * This prints the raw graph starting from the first node based on loading.
 * Prints each node and its neighborows.
 * 
 * @param graph Graph that should be printed
 * 
 * This part of the code was provided to me by mr. Kot in CV5.
 * However it is slightly modified for this exact project.
*/
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