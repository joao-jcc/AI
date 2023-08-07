#include "maze.hpp"

// Default constructor
Maze::Maze() {
    _walls = std::vector< std::vector<bool> >() ;
    _start = Vec2();
    _goal = Vec2();
    _dimension = Vec2();

    _node = nullptr;
    _frontier = nullptr;

    _input_maze = "";
    
    _solution_found = false;
    _solution = std::vector<Vec2>();
    _explored_nodes = std::vector<Node*>();
    _trash_nodes = std::vector<Node*>();

}

// Constructor with specified frontier/key and input_maze
Maze::Maze(std::string input_maze, char key) : Maze() {
    set_frontier(key);
    read_maze(input_maze);
}

// Destructor of the Maze class. It releases the memory of all the Node objects in the _explored_nodes vector.
Maze::~Maze() {
    std::cout << TERMINAL_BOLDRED << "Destroying Maze!" << std::endl;
    for (Node* node : _explored_nodes) {
        delete node;
    }

    for (Node* node : _trash_nodes) {
        delete node;
    }

    delete _frontier;
}

// Function to read the maze from a file specified by the given path and initialize the internal maze representation.
// Fills _dimension, _goal, _start and _walls;
void Maze::read_maze(std::string input_maze) {
    if (_frontier == nullptr) {
        std::cerr << "Frontier must be set before to read a maze!" << std::endl;
        return;
    }

    std::ifstream file(input_maze);

    // Check if the file could be opened successfully.
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << input_maze << std::endl;
        return;
    }

    _input_maze = input_maze;

    // Clear the existing maze data.
    _walls.clear();

    float l = 0; // Initialize a line counter.
    float c;
    // Read the file line by line.
    std::string line;
    while (getline(file, line)) {
        std::vector<bool> row; // Create a vector to represent a row in the maze.

        // Process each character in the current line.
        for (c = 0; c < line.size(); ++c) {
            if (line[c] == '#') {
                // '#' character represents a wall.
                row.push_back(true);
                continue;
            } else if (line[c] == 'A') {
                // 'A' character represents the starting position in the maze.
                _start = Vec2{l, c};
            } else if (line[c] == 'B') {
                // 'B' character represents the goal position in the maze.
                _goal = Vec2{l, c};
            }
            row.push_back(false); // Any other character represents an open path.
        }
        _walls.push_back(row); // Add the row to the maze representation.
        ++l; // Increment the line counter.
    }
    
    _dimension = Vec2(l, c);

    file.close(); // Close the file after reading.
}


// Function to write the solution path into a file specified by the given path.
void Maze::report() {
    if (_solution.empty()) {
        std::cerr << "No solution to be reported!" << std::endl;
        return;
    }

    std::string path_report = _path_to_report();

    std::ofstream file(path_report);
    // Check if the file could be opened successfully.
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path_report << std::endl;
        return; // Exit the program with an error code 2.
    }

    // Write path cost and number of explored nodes
    file << "Search: " << _frontier->get_name() << std::endl;
    file << "Path Cost: " << _solution.size() - 1 << std::endl;
    file << "Explored Nodes: " << _explored_nodes.size() << std::endl;

    file << std::endl;

    // Create a maze representation with characters to be written into the file.
    std::vector< std::vector<std::string> > maze(_dimension.get_x(), std::vector<std::string>(_dimension.get_y(), " "));

    // Convert the maze data into characters for visualization.
    for (int l = 0; l < _dimension.get_x(); ++l) {
        for (int c = 0; c < _dimension.get_y(); ++c) {
            maze[l][c] = _walls[l][c] ? wall_unicode : free_unicode;
        }
    }

    for (Node* node: _explored_nodes) {
        maze[node->get_position().get_x()][node->get_position().get_y()] = explored_unicode;
    }

    // Mark the solution path in the maze representation.
    for (Vec2 position : _solution) {
        maze[position.get_x()][position.get_y()] = solution_unicode;
    }

    // Mark the start and goal positions in the maze representation.
    maze[_start.get_x()][_start.get_y()] = "A";
    maze[_goal.get_x()][_goal.get_y()] = "B";
    
    // Write the maze representation into the file.
    for (int l = 0; l < _dimension.get_x(); ++l) {
        for (int c = 0; c < _dimension.get_y(); ++c) {
            file << maze[l][c];
        }
        file << std::endl; // Add a new line after each row.
    }

    file << std::endl;
    file << "Solution:" << std::endl;


    for (Vec2 position : _solution) {
        file << "(" << std::setfill('0') << std::setw(2) << position.get_x() << ", " << std::setfill('0') << std::setw(2) << position.get_y() << ")" << std::endl;
    }


    file.close(); // Close the file after writing.
}


std::string Maze::_path_to_report() {
    std::string root = "reports/";
    size_t pos = _input_maze.find_last_of(".");

    std::string frontier_sufix = _frontier->get_name().substr(0, 2);
    transform(frontier_sufix.begin(), frontier_sufix.end(), frontier_sufix.begin(), ::tolower);
    std::string path = _input_maze.substr(0, pos) + frontier_sufix + "-report.txt";
    pos = _input_maze.find_first_of("/");
     
    return root + path.substr(pos + 1);
}


std::vector<Vec2> Maze::actions(Node* node) {
    Vec2 position = node->get_position();
    int l = position.get_x();
    int c = position.get_y();
    std::vector<Vec2> options;

    // Down
    if (l < _dimension.get_x() - 1 && !_walls[l + 1][c]) {
        options.push_back(Vec2{1, 0});
    }
    // Up
    if (l > 0 && !_walls[l - 1][c]) {
        options.push_back(Vec2{-1, 0});
    }
    // Right
    if (c < _dimension.get_y() - 1 && !_walls[l][c + 1]) {
        options.push_back(Vec2{0, 1});
    }
    // Left
    if (c > 0 && !_walls[l][c - 1]) {
        options.push_back(Vec2{0, -1});
    }

    return options;
}

Node* Maze::result(Node* node, Vec2 action) {
    Vec2 new_position = Vec2{node->get_position().get_x() + action.get_x(), node->get_position().get_y() + action.get_y()};
    Node* new_node = new Node{new_position, action, node};

    return new_node;
}

bool Maze::explored(Node* target_node) {
    for (Node* node : _explored_nodes) {
        if(*target_node == *node) {
            return true;
        }
    }

    return false;
}

void Maze::solve() {
    Node* start_node = new Node{_start, Vec2(), nullptr};
    _frontier->add(start_node);

    Node* node = new Node();
    while(!_solution_found) {
        _solve_step();
    }

    while(_node->get_parent() != nullptr) {
        _solution.insert(_solution.begin(), _node->get_position());
        _node = _node->get_parent();
    }
    _solution.insert(_solution.begin(), _node->get_position());
}

void Maze::_solve_step() {
     if (_frontier->empty()) {
            std::cerr << "No Solution found!" << std::endl;
            return;
        }

        _node = _frontier->remove();
        _explored_nodes.push_back(_node);
  
        if (_node->get_position() == _goal) {
           _solution_found = true;
           return;
        }

        for (Vec2 action : actions(_node)) {
            Node* temp_node = result(_node, action);
            if (!(_frontier->contains_state(temp_node)) && !explored(temp_node)) {
                _frontier->add(temp_node);
            } else {
                _trash_nodes.push_back(temp_node);
            }
        }
}

void Maze::set_frontier(char key) {
    if (_frontier == nullptr) {
        delete _frontier;
    } 

    switch (key) {
        case 's':
            _frontier = new StackFrontier();
            _frontier->set_name("Stack Frontier");
            break;
        
        case 'q':
            _frontier = new QueueFrontier();
            _frontier->set_name("Queue Frontier");
            break;
        
        default:
            std::cerr << ("Available keys: s, q") << std::endl;
            break;
    }

}


