#pragma once
#include "loadGraph.h"

class DFSIterator{
    public:
        Graph graph;
        int numberOfComponents;
        std::queue<Node *> startingNodeOfComponent;
        std::stack<Node *> DFSstack;
        Node* current;
        bool first;
        
        /**
         * @param gra Graph for DFS iterator
        */
        DFSIterator(Graph gra);

        /**
         * Destructor for DFS iterator
        */
        ~DFSIterator();

        /**
         * This method saves each component's node with lowest number 
        */
        void Reset();

        /**
         * This method moves to next node
        */
        void Next();

        /**
         * This method checks the iterator ended
         * 
         * \retval FALSE if iterator is not on the end yet
         * \retval TRUE iterator ended
        */
        bool IsEnd();

        /**
         * This method returns ID of current node
         * 
         * @return ID of current node
        */
        int CurrentKey();

};