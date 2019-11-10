#include "label.hpp"

Label::Label(Window *parent, const char *text, int x, int y, int width, int height)
        : GUIObject(parent, "Static", 0, text, x, y, width, height) {}
