#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "raylib.h"
#include "Colors.hpp"
#include <iostream>


class Vec2 {
    private:
        float _x;
        float _y;
    
    public:
        Vec2();
        Vec2(float x, float y);
        ~Vec2();

        void print(); 

        bool operator==(const Vec2& other) const;

        float min();
        float max();

        float get_x() const {
            return _x;
        };   

        float get_y() const {
            return _y;
        }
};

class Node {
    private:
        Vec2 _position;
        Vec2 _action;
        Node* _parent;
    
    public:
        Node(Vec2 position = Vec2(), Vec2 action = Vec2(), Node* parent = nullptr);
        ~Node();

        bool operator==(const Node& other) const;
        void print();


        Vec2 get_position() const {
            return _position;
        }

        Vec2 get_action() const {
            return _action;
        }

        Node* get_parent() const {
            return _parent;
        }
};

#endif