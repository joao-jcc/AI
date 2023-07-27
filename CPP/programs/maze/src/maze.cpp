#include "maze.hpp"

Maze::Maze(std::string path) {
    read_maze(path);
}

Maze::~Maze() {
    for (Node* node : _explored_nodes) {
        delete node;
    }
}

void Maze::read_maze(std::string path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
        exit(2);
    }

    _walls.clear();

    int l = 0;
    std::string line;
    while (getline(file, line)) {
        std::vector<bool> row;
        for (int c = 0; c < line.size(); ++c) {
            if (line[c] == '#') {
                row.push_back(true);
                continue;
            } else if (line[c] == 'A') {
                _start = Vector2{l, c};
            } else if (line[c] == 'B') {
                _goal = Vector2{l, c};
            }
            row.push_back(false);
        }
        _walls.push_back(row);
        ++l;
    }

    file.close();
}

void Maze::write_solution(std::string path) {
    if (_solution.empty()) {
        std::cerr << "No solution to be written!" << std::endl;
        exit(3);
    }

    std::ofstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
        exit(2);
    }

    int n_lines = _walls.size();
    int n_cols = _walls.at(0).size();

    std::vector<std::vector<char>>maze(n_lines, std::vector<char>(n_cols, ' '));
    
    for (int l=0; l < n_lines; ++l) {
        for (int c=0; c < n_cols; ++c) {
            maze[l][c] = _walls[l][c] ? '#' : ' ';
        }
    }
    maze[_start.x][_start.y] = (char)'A';
    maze[_goal.x][_goal.y] = (char)'B';

    for (Vector2 position : _solution) {
        maze[position.x][position.y] = '*';
    }
    
    for (int l=0; l < n_lines; ++l) {
        for (int c=0; c < n_cols; ++c) {
            file << maze[l][c];
        }
        file << std::endl;
    }
    file.close();
}