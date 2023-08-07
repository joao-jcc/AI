#ifndef MAZE_HPP
#define MAZE_HPP

#include "raylib.h"
#include "frontier.hpp"
#include "cell.hpp"
#include "settings.hpp"
#include <fstream>
#include <map>
#include <string>

class Maze {
    protected:
        // Maze shape and qualifiers
        std::vector<std::vector<bool>> _walls;
        Vec2 _start;
        Vec2 _goal;
        Vec2 _dimension;

        std::string _input_maze;

        // Current Node
        Node* _node;
        // Solution: A + intermediate_states + B
        std::vector<Vec2> _solution;
        // Frontier
        Frontier* _frontier;
        // Explored Nodes: A + all other explored nodes + B
        std::vector<Node*> _explored_nodes;
        // Trash nodes to avoid memory leak
        std::vector<Node*> _trash_nodes;
        // Solution flag
        bool _solution_found;

        // gen path to report
        std::string _path_to_report();

        // Step search into maze: removes and expands the node checkinh if it is the goal
        void _solve_step();
    
    public:
        // Default Constructor
        Maze();
        // Constructor with specified maze input and key frontier
        Maze(std::string input_maze, char key);
        ~Maze();

        // I/O functions
        void read_maze(std::string input_maze);

        void report();

        std::vector<Vec2> actions(Node* node);
        Node* result(Node* node, Vec2 action);

        // Total search into maze
        void solve();

        bool explored(Node* node);

        // Getters
        Vec2 get_start() {
            return _start;
        };

        Vec2 get_goal() {
            return _goal;
        }

        Vec2 get_dimension() {
            return _dimension;
        }

        std::vector<std::vector<bool>> get_walls() {
            return _walls;
        }
        
        // Setters
        void set_frontier(char key);

};

#endif