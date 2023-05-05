#include "iterator.h"


static int iterator = 0;

Iterator::Iterator(Graph gra){
    this->graph = gra;
    this->isEnd = false;
    iterator = 0;
}
Iterator::~Iterator(){
    delete[] this->graph.nodes;
    this->graph.nodes = nullptr;
    this->numberOfComponents = 0;
    this->startingComponents.clear();
    this->isEnd = false;
    iterator = 0;
}


void Iterator::PrintInfo(){
    std::cout << "This graph is divided into " << this->numberOfComponents << " components and their starting points are:" << std::endl;
    for (std::vector<Node*>::size_type i=1; i<this->startingComponents.size() + 1; i++){
        std::cout << "     " << i << ". component: " << startingComponents[i-1]->id << std::endl;
    } 
}


void Iterator::ResetStatuses(){
    for (int i=0; i<this->graph.count; i++){
        this->graph.nodes[i].status = visited;
    }
}


void Iterator::Reset(Graph testGrap){

    std::vector<Node *> start_in_components;

    for (int i=0; i<testGrap.count; i++){
        if (testGrap.nodes[i].status == visited){
            Node* currentNode = &testGrap.nodes[i];

            Node* lowest = currentNode;
            
            std::stack<Node *> stack;
            stack.push(currentNode);
            currentNode->status = processing;

            while( !stack.empty() ){
                Node* currentNode = stack.top();
                stack.pop();

                if (currentNode->id < lowest->id){
                    lowest->id = currentNode->id;
                }

                for (std::vector<Node *>::size_type j=0; j<currentNode->neighbors.size(); j++){
                    if( currentNode->neighbors[j]->status == visited ){
                        stack.push(currentNode->neighbors[j]);
                        currentNode->neighbors[j]->status = processing;
                    }
                }
                currentNode->status = visited;
            }

            start_in_components.push_back(lowest);
        }
    }

    this->numberOfComponents = start_in_components.size();
    this->startingComponents = start_in_components;
    this->ResetStatuses();
}


void Iterator::CurrentKey(int id){
    std::cout << "     " << iterator << ". " << id << " " << std::endl;
    iterator++;
}


bool Iterator::IsEnd(std::stack<Node *> st){
    if ( st.empty()){
        isEnd = true;
    } 

    return this->isEnd;
}


bool Iterator::IsEnd(std::queue<Node *> qu){
    if ( qu.empty()){
        isEnd = true;
    } 

    return this->isEnd;
}


void Iterator::DoDFS(){
    this->ResetStatuses();
    iterator = 0;

    std::cout << "\nDepth First Search:" << std::endl;
    for (std::vector<Node*>::size_type j=1; j<this->startingComponents.size() + 1; j++){
        std::cout << j <<". component and iterator over it:" << std::endl;
        
        std::stack<Node *> stack;
        Node* current = this->startingComponents[j-1];
        stack.push(current);
        current->status = processing;

        while ( !IsEnd(stack) ){
            Node* currentInLoop = stack.top();
            stack.pop();

            this->CurrentKey(currentInLoop->id);

            for (std::vector<Node *>::size_type i=0; i<currentInLoop->neighbors.size(); i++){
                if(currentInLoop->neighbors[i]->status == visited){
                    stack.push(currentInLoop->neighbors[i]);
                    currentInLoop->neighbors[i]->status = processing;
                }
            }
            currentInLoop->status = visited;           
        }
        this->isEnd = false;
    }
}


void Iterator::DoBFS(){
    this->ResetStatuses();
    iterator = 0;

    std::cout << "\nBreadth First Search:" << std::endl;
    for (std::vector<Node*>::size_type j=1; j<this->startingComponents.size() + 1; j++){
        std::cout << j <<". component and iterator over it:" << std::endl;
        
        std::queue<Node *> queue;
        Node* current = this->startingComponents[j-1];
        queue.push(current);
        current->status = processing;

        while ( !IsEnd(queue) ){
            Node* currentInLoop = queue.front();
            queue.pop();

            this->CurrentKey(currentInLoop->id);

            for (std::queue<Node *>::size_type i=0; i<currentInLoop->neighbors.size(); i++){
                if(currentInLoop->neighbors[i]->status == visited){
                    queue.push(currentInLoop->neighbors[i]);
                    currentInLoop->neighbors[i]->status = processing;
                }
            }
            currentInLoop->status = visited;           
        }
        this->isEnd = false;
    }
}