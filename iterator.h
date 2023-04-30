#pragma once
#include "loadGraph.h"

class Iterator{
    private:
        Graph graph;
        int numberOfComponents;
        std::vector<Node *> startingComponents;
        bool isEnd;
    public:
        Iterator(Graph gra);
        ~Iterator();
        void PrintInfo();
        void ResetStatuses();
        
        void Reset(Graph testGrap);
        void CurrentKey(int id);
        bool IsEnd(std::stack<Node *> st);
        bool IsEnd(std::queue<Node *> qu);
        void DoDFS();
        void DoBFS();
};
