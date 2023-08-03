#include "maze.hpp"
#include "maze-app.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: [executable] [input_maze]" << std::endl;
        exit(1);
    }

    std::string input_maze = argv[1];
    MazeApp app(input_maze);
    app.run();

    // // read
    // std::string input_maze = argv[1];
    // Maze maze(input_maze);

    // // solve
    // maze.solve();

    // // write
    // size_t pos = input_maze.find_last_of(".");
    // std::string output_maze = input_maze.substr(0, pos) + "-solution.txt";
    

    // maze.write_solution(output_maze);

    

    std::cout << TERMINAL_BOLDGREEN << "SUCESSO!" <<  TERMINAL_RESET <<std::endl;

    return 0;
}