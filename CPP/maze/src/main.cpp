#include "maze.hpp"
#include "maze-app.hpp"
#include "CLI11.hpp" 
#include <iostream>

int main(int argc, char* argv[]) {
    CLI::App app("Maze Solver");

    std::string option;
    std::string input_maze;
    std::string frontier_option;  // Option to specify stack or queue

    app.add_option("--option", option, "Choose option: maze or mazeApp")->required();
    app.add_option("--input_maze", input_maze, "Input maze file")->required();
    app.add_option("--frontier", frontier_option, "Frontier type: stack or queue")->required();

    CLI11_PARSE(app, argc, argv);

    char frontier_key;
    if (!frontier_option.empty()) {
        if (frontier_option == "stack") {
            frontier_key = 's';
        } else if (frontier_option == "queue") {
            frontier_key = 'q';
        } else {
            std::cerr << "Invalid frontier option: " << frontier_option << std::endl;
            exit(1);
        }
    }

    if (option == "maze") {
        // execute Maze
        // read
        Maze maze(input_maze, frontier_key);

        // solve
        maze.solve();

        // write
        size_t pos = input_maze.find_last_of(".");
        std::string output_maze = input_maze.substr(0, pos) + "-solution.txt";
        maze.write_solution(output_maze);

        std::cout << "Maze solved successfully!" << std::endl;
    } else if (option == "mazeApp") {
        // execute MazeApp
        MazeApp mazeApp(input_maze, frontier_key);

        mazeApp.run();

        std::cout << "MazeApp executed successfully!" << std::endl;
    } else {
        std::cerr << "Options: mazeApp, maze" << option << std::endl;
        exit(1);
    }

    return 0;
}
