#ifndef CELL_HPP
#define CELL_HPP

#include "raylib.h"

class Cell {
    private:
        Rectangle _rectangle;
        Color _color;
        Vector2 _position;

    public:
        Cell(Rectangle& rectangle, Color& color, Vector2& position);    
        ~Cell();
        void draw();
};

#endif