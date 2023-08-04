#include "cell.hpp"

Cell::Cell() {
    
}

Cell::Cell(Rectangle& rectangle, Color& color, Vec2& position) 
: _rectangle(rectangle), _color(color), _position(position) {

}

Cell::~Cell() {

}

void Cell::draw() {
    DrawRectangle(_rectangle.x, _rectangle.y, _rectangle.width, _rectangle.height, _color);
    DrawRectangleLinesEx(_rectangle, 1, BLACK);
}

