#ifndef CELL_HPP
#define CELL_HPP

#include "raylib.h"
#include "utilities.hpp"

class Cell {
    private:
        Rectangle _rectangle;
        Color _color;
        Vec2 _position;

    public:
        Cell();
        Cell(Rectangle& rectangle, Color& color, Vec2& position);    
        ~Cell();
        void draw();

        void set_color(Color color) {
            _color = color;
        }

        Rectangle get_rectangle() const {
            return _rectangle;
        }

        Color get_color() const {
            return _color;
        }

        Vec2 get_position() const {
            return _position;
        }
};

#endif