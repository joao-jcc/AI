#ifndef MAZE_APP_HPP
#define MAZE_APP_HPP


#include "maze.hpp"
#include "cell.hpp"
#include <map>

const float CELL_SIZE = 40.0f;
const Rectangle Menu = Rectangle {}; 
const Color goal_color = Color{255, 0, 0, 255};
const Color start_color = Color{0, 171, 28, 255};
const Color wall_color = Color{40, 40, 40, 255};
const Color free_color = Color{237, 240, 252, 255};
const Color solution_color = Color{220, 235, 113, 255};
const Color explored_color = Color{212, 97, 85, 255};
const Color frontier_color = Color{255, 150, 130, 255};

const Color stats_color = Color{237, 240, 252, 255};
const float stats_height = 30.0f;

/* Maze class with graphical features */
class MazeApp : public Maze {
    private:
        // Screen dimensions
        Vec2 _screen;

        // Cells that fill the maze
        std::map<int, Cell> _cells;

        // Current node
        Node* _node;

        // Solution flag
        bool _solution_found;

        // Stats
        Rectangle _stats;

        // Time
        float _clock;
        float _update_rate;

        // Solution index for final animation
        int _solution_idx;

        // Auxiliar function that generates the cells
        void _gen_cells();

        // Update maze
        void _update_maze();

        // Update Cells
        void _update_cells();

        // Gen code based on Vec2 position
        int _gen_code(Vec2 position);

        // Set solution
        void _set_solution();

        // Draw stats
        void _draw_stats();


    public:
        MazeApp(std::string path, char frontier_key);
        ~MazeApp();

        // run the application with render loop
        void run();
        
        // update app state: cells, node, frontier, explored nodes
        void update();

        // Desenha os objetos
        void draw();
};

#endif