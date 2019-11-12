#include "label.hpp"

Label::Label(const char *text, int x, int y, int width, int height) : Label(nullptr, text, x, y, width, height) {}

Label::Label(Window *parent, const char *text, int x, int y, int width, int height)
        : GUIObject(parent, "Static", 0L, text, x, y, width, height) {}
