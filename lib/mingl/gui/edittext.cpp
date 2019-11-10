#include "edittext.hpp"

EditText::EditText(Window *parent, const char *text, int x, int y, int width, int height)
        : GUIObject(parent, "Edit", 0, text, x, y, width, height) {}
