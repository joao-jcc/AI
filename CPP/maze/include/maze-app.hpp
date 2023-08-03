#ifndef MAZE_APP_HPP
#define MAZE_APP_HPP


#include "maze.hpp"
#include "cell.hpp"

const float CELL_SIZE = 50.0f;
const Color start_color = Color{0, 200, 0, 255};
const Color goal_color = Color{200, 0, 0, 255};
const Color wall_color = Color{50, 50, 50, 255};
const Color free_color = Color{102, 191, 255, 255};
const Color solution_color = Color{100, 100, 0, 255};
const Color explored_color = Color{50, 0, 0, 255};

/* Maze class with graphical features */
class MazeApp : public Maze {
    private:
        Vector2 _screen;
        std::vector<Cell> _cells;
        void _gen_cells();
        Node* _node; // current node
        bool _solution_found;

    public:
        MazeApp(std::string path);
        ~MazeApp();

        void run();
        void update();
        void draw();
};

#endif