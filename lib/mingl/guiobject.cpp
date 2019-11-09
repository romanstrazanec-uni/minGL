#include "guiobject.hpp"

GUIObject::GUIObject(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

int GUIObject::getX() const {
    return x;
}

int GUIObject::getY() const {
    return y;
}

int GUIObject::getWidth() const {
    return width;
}

int GUIObject::getHeight() const {
    return height;
}
