#ifndef MAZE_HPP
#define MAZE_HPP

#include "frontier.hpp"
#include <fstream>
#include <string>

class Maze {
    protected:
        // Maze shape and qualifiers
        std::vector<std::vector<bool>> _walls;
        Vector2 _start;
        Vector2 _goal;
        Vector2 _dimension;

        // Solution: A + intermediate_states + B
        std::vector<Vector2> _solution;
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

        std::vector<Vector2> actions(Node* node);
        Node* result(Node* node, Vector2 action);
        void solve();

        bool explored(Node* node);

        // Getters
        Vector2 get_vector2(char key);
        std::vector<std::vector<bool>> get_walls();
};

#endif