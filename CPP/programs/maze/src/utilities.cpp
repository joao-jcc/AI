#include "utilities.hpp"

StackFrontier::StackFrontier() {
    _frontier = std::vector<Node*>();
}

StackFrontier::~StackFrontier() {

}

void StackFrontier::add(Node* node) {
    _frontier.push_back(node);
}

bool StackFrontier::contains_state(Node* target_node) {
    for (Node* node : _frontier) {
        if (*node == *target_node) {return true;}
    }
    return false;
}

bool StackFrontier::empty() {
    return _frontier.empty();
}

Node* StackFrontier::remove() {
    if (empty()) {
        throw std::runtime_error("Frontier is empty!");
    }
    Node* last_node = _frontier.back();
    _frontier.pop_back();

    return last_node;
}


