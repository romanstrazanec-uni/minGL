#include "edittext.hpp"

EditText::EditText(long id, int x, int y, int width, int height)
        : EditText(nullptr, id, "", x, y, width, height) {}
EditText::EditText(long id, const char *text, int x, int y, int width, int height)
        : EditText(nullptr, id, text, x, y, width, height) {}
EditText::EditText(Window *parent, long id, int x, int y, int width, int height)
        : EditText(parent, id, "", x, y, width, height) {}
EditText::EditText(Window *parent, long id, const char *text, int x, int y, int width, int height)
        : GUIObject(parent, "Edit", id, text, x, y, width, height) {}
