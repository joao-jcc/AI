#include  "maze-app.hpp"

MazeApp::MazeApp(std::string path) : Maze(path) {
    _gen_cells();
    _screen = Vector2{ _dimension.y * CELL_SIZE, _dimension.x * CELL_SIZE };
    _node = new Node{_start, Vector2{0, 0}, nullptr};
    _frontier->add(_node);
    _solution_found = false;
}

MazeApp::~MazeApp() {

}


void MazeApp::run() {
    // Initialize Window
    InitWindow(_screen.x, _screen.y, "Maze");

     // Render Loop
    while(!WindowShouldClose()) {
        //update
        update();
        // draw
        draw();
    }

    // Close openGL state
    CloseWindow();

}

void MazeApp::update() {
    if (_solution_found) {
        return;
    }
    
    if (_frontier->empty()) {
        std::cerr << "No Solution!" << std::endl;
        exit(5);
    }


    _node = _frontier->remove();
    _explored_nodes.push_back(_node);        
    if (equal_v2(_node->position, _goal)) {
        _solution_found = true;
        return;
    }

    for (Vector2 action : actions(_node)) {
        Node* temp_node = result(_node, action);
        if (!(_frontier->contains_state(temp_node)) && !explored(temp_node)) {
            _frontier->add(temp_node);
        } else {
            _trash_nodes.push_back(temp_node);
        }
    }
}

void MazeApp::draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    for (Cell cell : _cells) {
        cell.draw();
    }

    EndDrawing();
}


void MazeApp::_gen_cells() {
    for (int l=0; l < _dimension.x; ++l) {
        for (int c=0; c < _dimension.y; ++c) {
            Rectangle rec{c * CELL_SIZE, l * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            Vector2 position{(float) l, (float) c};
            Color color;
            if (_start.x == l && _start.y == c) {
                color = start_color;
            } else if (_goal.x == l && _goal.y == c) {
                color = goal_color;
            } else {
                color = _walls[l][c] ? wall_color : free_color;
            }

            Cell cell(rec, color, position);
            _cells.push_back(cell);
        }
    }
}
