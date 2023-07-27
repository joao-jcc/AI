#ifndef MAZE_HPP
#define MAZE_HPP

#include "utilities.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class Maze {
    private:
        std::vector<std::vector<bool>> _walls;
        Vector2 _start;
        Vector2 _goal;

        std::vector<Vector2> _solution;
        StackFrontier stack_frontier;
        std::vector<Node*> _explored_nodes;
    
    public:
        Maze(std::string path);
        ~Maze();

        // I/O functions
        void read_maze(std::string path);
        void write_solution(std::string path);

        std::vector<Vector2> actions(Node* node);
        Node* result(Node* node, Vector2 action);
        void solve();
};

#endif