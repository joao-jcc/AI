#include "maze.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: [executable] [input_maze] [frontier_key]" << std::endl;
        exit(1);
    }

    // input_maze
    std::string input_maze = argv[1];
    char frontier_key = argv[2][0];
 
    // Initialize empty maze
    Maze maze;
    // Set frontier accordinly to key: s for stack and q for queue
    maze.set_frontier(frontier_key);
    // Read a maze
    maze.read_maze(input_maze);
    // Solve
    maze.solve();
    // report
    maze.report();


    return 0;
}
