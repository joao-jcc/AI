#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "raylib.h"
#include "Colors.hpp"
#include <iostream>

inline bool equal_v2(Vector2 v1, Vector2 v2) {
    return v1.x == v2.x && v1.y == v2.y;
};

inline void print_v2(Vector2 v) {
    std::cout << TERMINAL_BOLDBLUE << "(" << v.x << "," << v.y << ")" << TERMINAL_RESET << std::endl;
};

typedef struct Node {
    Vector2 position;
    Vector2 action;
    Node* parent;
} Node;

// The path must be the same
inline bool equal_node(Node* n1, Node* n2) {
    // Node not equal at the position and action
    // return equal_v2(n1->position, n2->position) && equal_v2(n1->action, n2->action);
    return equal_v2(n1->position, n2->position);
};

inline void print_node(Node* node) {
    std::cout << TERMINAL_BOLDCYAN << "---NODE---" << TERMINAL_RESET << std::endl;
    std::cout << "act: ";
    print_v2(node->action);
    std::cout << "pos: ";
    print_v2(node->position);
    std::cout << TERMINAL_BOLDMAGENTA << "adr: " << node->parent << TERMINAL_RESET << std::endl;
};


#endif