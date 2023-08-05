#include "frontier.hpp"

// FRONTIER BASE

Frontier::Frontier() {
    _frontier = std::vector<Node*>();
}

Frontier::~Frontier() {

}

void Frontier::add(Node* node) {
    _frontier.push_back(node);
}

bool Frontier::contains_state(Node* target_node) {
    for (Node* node : _frontier) {
        if (*node == *target_node) {return true;}
    }
    return false;
}

bool Frontier::empty() {
    return _frontier.empty();
}

int Frontier::size() {
    return _frontier.size();
}

// STACK FRONTIER

StackFrontier::StackFrontier() {

}

StackFrontier::~StackFrontier() {

}

Node* StackFrontier::remove() {
    if (empty()) {
        throw std::runtime_error("Frontier is empty!");
    }
    Node* last_node = _frontier.back();
    _frontier.pop_back();

    return last_node;
}


// QUEUE FRONTIER

QueueFrontier::QueueFrontier() {

}

QueueFrontier::~QueueFrontier() {

}

Node* QueueFrontier::remove() {
    if (empty()) {
        throw std::runtime_error("Frontier is empty!");
    }
    Node* first_node = _frontier.at(0);
    _frontier.erase(_frontier.begin());

    return first_node;
}