#ifndef FRONTIER_HPP
#define FRONTIER_HPP

#include "utilities.hpp"

class Frontier {
    protected:
        std::vector<Node*> _frontier;
    
    public:
        Frontier();
        virtual ~Frontier();

        void add(Node* node);
        bool contains_state(Node* node);
        bool empty();
        virtual Node* remove() = 0;

        std::vector<Node*> get_frontier() {
            return _frontier;
        }

};

class StackFrontier : public Frontier {
    public:
        StackFrontier();
        ~StackFrontier();

        Node* remove() override;
};

class QueueFrontier : public Frontier {
    public:
        QueueFrontier();
        ~QueueFrontier();

        Node* remove() override;
};


#endif