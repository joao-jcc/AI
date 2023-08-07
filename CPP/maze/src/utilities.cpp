#include "utilities.hpp"

// Vec2

Vec2::Vec2() {

}

Vec2::Vec2(float x, float y) : _x(x), _y(y) {

}

Vec2::~Vec2() {

}

bool Vec2::operator==(const Vec2& other) const {
    return _x == other.get_x() && _y == other.get_y();
};

void Vec2::print() {
    std::cout << TERMINAL_BOLDBLUE << "(" << _x << "," << _y << ")" << TERMINAL_RESET << std::endl;
}

float Vec2::min() {
    return _x < _y ? _x : _y;
}

float Vec2::max() {
    return _x > _y ? _x : _y;
}

// Node

Node::Node(Vec2 position, Vec2 action, Node* parent)
: _position(position), _action(action), _parent(parent) {

}

Node::~Node() {

}

bool Node::operator==(const Node& other) const {
    return _position == other.get_position();
}

void Node::print() {
    std::cout << TERMINAL_BOLDCYAN << "---NODE---" << TERMINAL_RESET << std::endl;
    std::cout << "act: ";
    _action.print();
    std::cout << "pos: ";
    _position.print();
    std::cout << TERMINAL_BOLDMAGENTA << "adr: " << _parent << TERMINAL_RESET << std::endl;
}