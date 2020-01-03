#include "label.hpp"

Label::Label(long id, const char *text, int x, int y, int width, int height)
        : Label(nullptr, id, text, x, y, width, height) {}

Label::Label(Window *parent, long id, const char *text, int x, int y, int width, int height)
        : GUIObject(parent, "Static", id, text, x, y, width, height) {}
