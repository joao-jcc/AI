#ifndef MAZE_HPP
#define MAZE_HPP

#include "frontier.hpp"
#include <fstream>
#include <string>

class Maze {
    protected:
        // Maze shape and qualifiers
        std::vector<std::vector<bool>> _walls;
        Vec2 _start;
        Vec2 _goal;
        Vec2 _dimension;

        // Solution: A + intermediate_states + B
        std::vector<Vec2> _solution;
        // Frontier
        Frontier* _frontier;
        // Explored Nodes: A + all other explored nodes + B
        std::vector<Node*> _explored_nodes;

        // Trash nodes to avoid memory leak
        std::vector<Node*> _trash_nodes;
    
    public:
        Maze(std::string path);
        ~Maze();

        // I/O functions
        void read_maze(std::string path);
        void write_solution(std::string path);

        std::vector<Vec2> actions(Node* node);
        Node* result(Node* node, Vec2 action);
        void solve();

        bool explored(Node* node);

        // Getters
        Vec2 get_Vec2(char key);
        std::vector<std::vector<bool>> get_walls();
};

#endif