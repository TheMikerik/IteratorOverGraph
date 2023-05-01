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


/**
 * Print each component of the graph and the node thats used as a starting point for following algorithms
*/
void Iterator::PrintInfo(){
    std::cout << "This graph is divided into " << this->numberOfComponents << " components and their starting points are:" << std::endl;
    for (std::vector<Node*>::size_type i=1; i<this->startingComponents.size() + 1; i++){
        std::cout << "     " << i << ". component: " << startingComponents[i-1]->id << std::endl;
    } 
}


/**
 * Resets statuses for all nodes.
*/
void Iterator::ResetStatuses(){
    for (int i=0; i<this->graph.count; i++){
        this->graph.nodes[i].status = UNCHECKED;
    }
}


/**
 * Reset function goes trough raw graph and it find all components of it.
 * Also it save the smallest number of each component for later use.
 * It does trough graph by using DFS algorithm.
 * 
 * @param testGraph Raw graph from which the number of components will be calculated
*/
void Iterator::Reset(Graph testGrap){

    std::vector<Node *> start_in_components;

    for (int i=0; i<testGrap.count; i++){
        if (testGrap.nodes[i].status == UNCHECKED){
            Node* currentNode = &testGrap.nodes[i];

            Node* lowest = currentNode;
            
            std::stack<Node *> stack;
            stack.push(currentNode);
            currentNode->status = CHECKING;

            while( !stack.empty() ){
                Node* currentNode = stack.top();
                stack.pop();

                if (currentNode->id < lowest->id){
                    lowest->id = currentNode->id;
                }

                for (std::vector<Node *>::size_type j=0; j<currentNode->neighbors.size(); j++){
                    if( currentNode->neighbors[j]->status == UNCHECKED ){
                        stack.push(currentNode->neighbors[j]);
                        currentNode->neighbors[j]->status = CHECKING;
                    }
                }
                currentNode->status = CHECKED;
            }

            start_in_components.push_back(lowest);
        }
    }

    this->numberOfComponents = start_in_components.size();
    this->startingComponents = start_in_components;
    this->ResetStatuses();
}


/**
 * Prints each node's position generated by iterator and also its.
 * 
 * @param id Id of the node
*/
void Iterator::CurrentKey(int id){
    std::cout << "     " << iterator << ". " << id << " " << std::endl;
    iterator++;
}


/**
 * Checking if the stack, that stores nodes from single component, is empty.
 * If so, it returns TRUE, otherwise its defaulty set as FLASE.
 * 
 * @param st Stack, that stores the components from each component
 * @return FALSE if stack is not empty, TRUE if it is empty
*/
bool Iterator::IsEnd(std::stack<Node *> st){
    if ( st.empty()){
        isEnd = true;
    } 

    return this->isEnd;
}


/**
 * Checking if the queue, that stores nodes from single component, is empty.
 * If so, it returns TRUE, otherwise its defaulty set as FLASE.
 * 
 * @param qu Queue, that stores the components from each component
 * @return FALSE if queue is not empty, TRUE if it is empty
*/
bool Iterator::IsEnd(std::queue<Node *> qu){
    if ( qu.empty()){
        isEnd = true;
    } 

    return this->isEnd;
}


/**
 * DoDFS goes trough graph by using Depth First Search algorithm.
 * The first step is reseting statuses of all nodes to make sure there
 * are no nodes with other status than UNCHECKED. Then it starts iterating
 * from the smallest number in each node.
 */
void Iterator::DoDFS(){
    this->ResetStatuses();
    iterator = 0;

    std::cout << "\nDepth First Search:" << std::endl;
    for (std::vector<Node*>::size_type j=1; j<this->startingComponents.size() + 1; j++){
        std::cout << j <<". component and iterator over it:" << std::endl;
        
        std::stack<Node *> stack;
        Node* current = this->startingComponents[j-1];
        stack.push(current);
        current->status = CHECKING;

        while ( !IsEnd(stack) ){
            Node* currentInLoop = stack.top();
            stack.pop();

            this->CurrentKey(currentInLoop->id);

            for (std::vector<Node *>::size_type i=0; i<currentInLoop->neighbors.size(); i++){
                if(currentInLoop->neighbors[i]->status == UNCHECKED){
                    stack.push(currentInLoop->neighbors[i]);
                    currentInLoop->neighbors[i]->status = CHECKING;
                }
            }
            currentInLoop->status = CHECKED;           
        }
        this->isEnd = false;
    }
}


/**
 * DoBFS goes trough graph by using Breadth First Search algorithm.
 * The first step is reseting statuses of all nodes to make sure there
 * are no nodes with other status than UNCHECKED. Then it starts iterating
 * from the smallest number in each node.
 * 
 * @return It prints each node's position generated by iterator and also its ID
*/
void Iterator::DoBFS(){
    this->ResetStatuses();
    iterator = 0;

    std::cout << "\nBreadth First Search:" << std::endl;
    for (std::vector<Node*>::size_type j=1; j<this->startingComponents.size() + 1; j++){
        std::cout << j <<". component and iterator over it:" << std::endl;
        
        std::queue<Node *> queue;
        Node* current = this->startingComponents[j-1];
        queue.push(current);
        current->status = CHECKING;

        while ( !IsEnd(queue) ){
            Node* currentInLoop = queue.front();
            queue.pop();

            this->CurrentKey(currentInLoop->id);

            for (std::queue<Node *>::size_type i=0; i<currentInLoop->neighbors.size(); i++){
                if(currentInLoop->neighbors[i]->status == UNCHECKED){
                    queue.push(currentInLoop->neighbors[i]);
                    currentInLoop->neighbors[i]->status = CHECKING;
                }
            }
            currentInLoop->status = CHECKED;           
        }
        this->isEnd = false;
    }
}