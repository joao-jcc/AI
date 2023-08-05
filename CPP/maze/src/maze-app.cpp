#include  "maze-app.hpp"

MazeApp::MazeApp(std::string path, char frontier_key) : Maze(path, frontier_key) {
    _screen = Vec2( _dimension.get_y() * CELL_SIZE, _dimension.get_x() * CELL_SIZE + stats_height);
    _stats = Rectangle{0, _screen.get_y() - stats_height, _screen.get_x(), _stats.height};
    _solution_found = false;
    _clock = 0.0f;
    _update_rate = 0.1f;
    _gen_cells();
}

MazeApp::~MazeApp() {
    std::cout << TERMINAL_BOLDRED << "Destruindo MazeApp!" << TERMINAL_RESET << std::endl;
}


void MazeApp::run() {
    // Initialize Window
    InitWindow(_screen.get_x(), _screen.get_y(), "Maze");
    
    // Start node
    _node = new Node(_start, Vec2(0, 0), nullptr);
    _frontier->add(_node);

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
    if (_clock < _update_rate) {
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
    _update_cells();

}

void MazeApp::_update_maze() {
    if (_frontier->empty()) {
        std::cout << "No Solution!" << std::endl;
        return;
    }

    _node = _frontier->remove();
    _explored_nodes.push_back(_node);

        
    if (_node->get_position() == _goal) {
        _set_solution();
        return;
    }

    std::vector<Vec2> options = actions(_node);
    for (Vec2 action : options) {
        Node* temp_node = result(_node, action);
        if (!(_frontier->contains_state(temp_node)) && !explored(temp_node)) {
            _frontier->add(temp_node);
        } else {
            _trash_nodes.push_back(temp_node);
        }
    }
}

void MazeApp::_update_cells() {
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

void MazeApp::draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    for (std::pair<int, Cell> pair : _cells) {
        pair.second.draw();
    }

    _draw_stats();

    EndDrawing();
}

void MazeApp::_draw_stats() {
    DrawRectangle(_stats.x, _stats.y, _stats.width, stats_height, stats_color);
    float width = _screen.get_x();
    if (width > 500) { 
        DrawText(TextFormat("Explored: %i", (int)_explored_nodes.size()), 20, _screen.get_y() - stats_height/1.5f, 20, wall_color);
        DrawText(TextFormat("Frontier: %i", (int)_frontier->size()), 170, _screen.get_y() - stats_height/1.5f, 20, wall_color);
        DrawText(TextFormat("Solution: "), 310, _screen.get_y() - stats_height/1.5f, 20, wall_color);
        DrawText(TextFormat(_solution_found ? "TRUE" : "FALSE"), 405, _screen.get_y() - stats_height/1.5f, 20, _solution_found ? GREEN : RED);
    } else if (width <= 500 && width > 160) {
        DrawText(TextFormat("exp: %i fro: %i sol:", (int)_explored_nodes.size(), (int)_frontier->size()), 20, _screen.get_y() - stats_height/1.5f, 10, wall_color);
        DrawText(TextFormat(_solution_found ? "true" : "false"), 110, _screen.get_y() - stats_height/1.5f, 10, _solution_found ? GREEN : RED);
    } else {
        std::cout << "Maze too small!" << std::endl;
        exit(6);
    }
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
