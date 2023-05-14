#include "DFSIterator.h"

DFSIterator::DFSIterator(Graph gra){
    this->graph = gra;
    this->numberOfComponents = 0;
    this->current = nullptr;
    this->first = true;
}
DFSIterator::~DFSIterator(){
    delete[] this->graph.nodes;
};

void DFSIterator::Reset(){
    Graph DFSgraph = this->graph;

    for (int i=0; i<DFSgraph.count; i++){               // Projdu vsechny originalni node pomoci DFS
        if (DFSgraph.nodes[i].status == not_visited){   // a najdu nejmensi cislo v kazde komponente
            Node* currentNode = &DFSgraph.nodes[i];

            Node* lowest = currentNode;
            
            std::stack<Node *> tmpStack;
            tmpStack.push(currentNode);                 // DFS pruchod pro hledani nejmensi node
            currentNode->status = processing;

            while( !tmpStack.empty() ){
                Node* currentNode = tmpStack.top();
                tmpStack.pop();

                if (currentNode->id < lowest->id){      // Pri pruchodu byla nalezena mensi hodnota
                    lowest->id = currentNode->id;
                }

                for (std::vector<Node *>::size_type j=0; j<currentNode->neighbors.size(); j++){
                    if( currentNode->neighbors[j]->status == not_visited ){
                        tmpStack.push(currentNode->neighbors[j]);
                        currentNode->neighbors[j]->status = processing;
                    }
                }
                currentNode->status = visited;
            }

            this->startingNodeOfComponent.push(lowest); // Konec jedne komponenty + predani lowest node 
        }
    }

    this->numberOfComponents = startingNodeOfComponent.size();

    for (int i=0; i<this->graph.count; i++){                // reset vsech zmenenych statusu
        this->graph.nodes[i].status = not_visited;
    }

    this->Next();
}

void DFSIterator::Next(){
    if ( this->DFSstack.empty() ){                      // Prvni/posledni pruchod
        if ( startingNodeOfComponent.empty() ){                 // posledni
            return;
        }
        else {                                                  // prvni node z kazde komponenty
            this->current = startingNodeOfComponent.front();
            this->current->status = processing;
            this->DFSstack.push(this->current);
            startingNodeOfComponent.pop();
        }
    }
    this->current = DFSstack.top();                  // Predavam hodnotu, ktera je zrovna na iteratoru
    DFSstack.pop();                                  // Je v current -> proto ji popnu
    
    
    for (std::vector<Node *>::size_type i=0; i<this->current->neighbors.size(); i++){       // Checkuju objevene/neobjevene sousedy
        if(this->current->neighbors[i]->status == not_visited){
            DFSstack.push(this->current->neighbors[i]);
            this->current->neighbors[i]->status = processing;
        }
    }
    this->current->status = visited;                   // Jakmile dochecknuju, nastavim na visited
}

bool DFSIterator::IsEnd(){
    if ( this->DFSstack.empty() && this->startingNodeOfComponent.empty() ){
        if (this->first){
            this->first = false;
            return false;
        }
        else {
            return true;
        }
    }
    else{
        return false;
    }
}

int DFSIterator::CurrentKey(){
    return this->current->id;
}