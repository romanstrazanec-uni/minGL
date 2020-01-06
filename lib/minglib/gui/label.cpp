#include "label.hpp"

Label::Label(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : Label(nullptr, id, text, x, y, width, height) {}
Label::Label(Window *parent, long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : GUIObject(parent, "Static", id, text, x, y, width, height) {}
