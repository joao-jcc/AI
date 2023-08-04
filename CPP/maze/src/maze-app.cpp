#include  "maze-app.hpp"

MazeApp::MazeApp(std::string path) : Maze(path) {
    _screen = Vec2( _dimension.get_y() * CELL_SIZE, _dimension.get_x() * CELL_SIZE );
    _solution_found = false;
    _clock = 0.0f;
    _update_time = 0.1f;
    _gen_cells();
}

MazeApp::~MazeApp() {

}


void MazeApp::run() {
    // Initialize Window
    InitWindow(_screen.get_x(), _screen.get_y(), "Maze");
    
    // Start node
    _node = new Node(_start, Vec2(0, 0), nullptr);
    _frontier->add(_node);

    float clock = 0.0f;
     // Render Loop
    while(!WindowShouldClose()) {
        // update
        update();

        // draw
        draw();
    }

    // Close openGL state
    CloseWindow();

}

void MazeApp::update() {   
    // update clock
    _clock += GetFrameTime();
    if (_clock < _update_time) {
        return;
    }
    _clock = 0.0f;

    // update solution
    if (_solution_found && _solution_idx >= 0) {
        Vec2 position = _solution.at(_solution_idx);
        
        if (!(position == _start || position == _goal)) {
          _cells.at(_gen_code(position)).set_color(solution_color);  
        }
        --_solution_idx;
        return;
    }

    if (_solution_found) {
        return;
    }

    // Change maze state
    _update_maze();

    // Change Cells color base on explored nodes and nodes in frontier
    for (Node* node : _explored_nodes) {
        Vec2 position = node->get_position();

        if (position == _start || position == _goal) {
            continue;
        }

        int code = _gen_code(node->get_position());
        _cells.at(code).set_color(explored_color);
    }

    for (Node* node : _frontier->get_frontier()) {
        Vec2 position = node->get_position();
        if (position == _start || position == _goal) {
            continue;
        }
        int code = _gen_code(position);
        _cells.at(code).set_color(frontier_color);
    }

}

void MazeApp::_update_maze() {
    if (_frontier->empty()) {
        std::cout << "No Solution!" << std::endl;
        return;
    }

    _node = _frontier->remove();
    _explored_nodes.push_back(_node);

    // std::cout << TERMINAL_BOLDRED << "REMOVED" << TERMINAL_RESET << std::endl;
    // _node->print();
        
    if (_node->get_position() == _goal) {
        _set_solution();
        return;
    }

    std::vector<Vec2> options = actions(_node);
    for (Vec2 action : options) {
        Node* temp_node = result(_node, action);
        if (!(_frontier->contains_state(temp_node)) && !explored(temp_node)) {
            std::cout << TERMINAL_BOLDRED << "ADICIONADO" << TERMINAL_RESET << std::endl;
            temp_node->print();
            _frontier->add(temp_node);
        } else {
            _trash_nodes.push_back(temp_node);
        }
    }

    // std::cout << TERMINAL_BOLDRED << "FRONTEIRA" << TERMINAL_RESET << std::endl;
    // for (Node* node: _frontier->get_frontier()) {
    //     node->print();
    // }
    
    // std::cout << TERMINAL_BOLDRED << "EXPLORED" << TERMINAL_RESET << std::endl;

    // for (Node* node: _explored_nodes) {
    //     node->print();
    // }

    // std::cout << TERMINAL_BOLDBLUE << "------------------" << TERMINAL_RESET << std::endl;
}

void MazeApp::draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    for (std::pair<int, Cell> pair : _cells) {
        pair.second.draw();
    }

    EndDrawing();
}


void MazeApp::_gen_cells() {
    for (int l=0; l < _dimension.get_x(); ++l) {
        for (int c=0; c < _dimension.get_y(); ++c) {
            Rectangle rec{c * CELL_SIZE, l * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            Vec2 position{(float) l, (float) c};
            Color color;
            if (_start.get_x() == l && _start.get_y() == c) {
                color = start_color;
            } else if (_goal.get_x() == l && _goal.get_y() == c) {
                color = goal_color;
            } else {
                color = _walls[l][c] ? wall_color : free_color;
            }

            Cell cell(rec, color, position);
            _cells[_gen_code(position)] = cell;
        }
    }
}

int MazeApp::_gen_code(Vec2 position) {
    return position.get_x() * _dimension.get_y() + position.get_y();
}

void MazeApp::_set_solution() {
    
    while(_node->get_parent() != nullptr) {
        _solution.insert(_solution.begin(), _node->get_position());
        _node = _node->get_parent();
    }
    _solution.insert(_solution.begin(), _node->get_position());

    _solution_found = true;
    _solution_idx = _solution.size() - 1;
}
