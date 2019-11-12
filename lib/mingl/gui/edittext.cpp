#include "edittext.hpp"

EditText::EditText(int x, int y, int width, int height) : EditText(nullptr, "", x, y, width, height) {}

EditText::EditText(const char *text, int x, int y, int width, int height)
        : EditText(nullptr, text, x, y, width, height) {}

EditText::EditText(Window *parent, int x, int y, int width, int height) : EditText(parent, "", x, y, width, height) {}

EditText::EditText(Window *parent, const char *text, int x, int y, int width, int height)
        : GUIObject(parent, "Edit", 0L, text, x, y, width, height) {}
