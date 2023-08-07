#include "utilities.hpp"

const std::string wall_unicode = "\u2588";
const std::string free_unicode = " ";
const std::string solution_unicode = "\u25E6";
const std::string explored_unicode = "\u2591";

const Color goal_color = Color{255, 0, 0, 255};
const Color start_color = Color{0, 171, 28, 255};
const Color wall_color = Color{40, 40, 40, 255};
const Color free_color = Color{237, 240, 252, 255};
const Color solution_color = Color{220, 235, 113, 255};
const Color explored_color = Color{212, 97, 85, 255};
const Color frontier_color = Color{255, 150, 130, 255};

const Color stats_color = Color{237, 240, 252, 255};
const float stats_height = 30.0f;

const Vec2 screen_dimension = Vec2(1200, 800);
const float cell_size = 40.0f;