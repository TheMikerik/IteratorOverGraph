#include "loadGraph.h"

int GetLines(std::string filename){
    std::ifstream inputFile(filename); 
    int numLines = 0;
    std::string line;

    while (getline(inputFile, line)){           // Ziskam pocet radku
        numLines++;
    }

    inputFile.close();
    return numLines;
}


int GetNodeCount(std::string filename){         // Nachazim originalni node
    int from, to;
    std::vector<int> isPart;
    int lines = GetLines(filename);

    bool checkFrom = false;
    bool checkTo = false;
    std::ifstream infile(filename);
    for(int i=0; i<lines; i++){
        infile >> from >> to;
        
        for (std::vector<int>::size_type j=0; j<isPart.size(); j++){
            if ( isPart[j] == from ){           // Prochazim vsechny nactene node
                checkFrom = true;               // pokud se node opakuje, tak ji nepridam
            }
            if ( isPart[j] == to ){
                checkTo = true;
            }
        }
        if (checkFrom == false){                // Pokud se neopakuje, tak ji zde pridavam
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
    Graph graph = {nodes, count};           // Tvorba empty grafu

    for (int i = 0; i < count; i++) {
        nodes[i].id = i;
    }
    for (int i=0; !infile.eof(); i++){
        infile >> from >> to;               // Pridavam sousedy
        if (!infile.fail()) {
            nodes[from].neighbors.push_back(nodes + to);
            nodes[to].neighbors.push_back(nodes + from);
        }
    }
    infile.close();	
    return graph;
}