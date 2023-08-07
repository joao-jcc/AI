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

        std::string _name;

        std::vector<Node*> get_frontier() {
            return _frontier;
        }

        std::string get_name() {
            return _name;
        }

        void set_name(std::string name) {
            _name = name;
        }

        int size();

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