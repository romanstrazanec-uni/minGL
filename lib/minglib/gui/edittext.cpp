#include "edittext.hpp"

EditText::EditText(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : EditText(nullptr, id, "", x, y, width, height) {}
EditText::EditText(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : EditText(nullptr, id, text, x, y, width, height) {}
EditText::EditText(Window *parent, long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : EditText(parent, id, "", x, y, width, height) {}
EditText::EditText(Window *parent, long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : GUIObject(parent, "Edit", id, text, x, y, width, height) {}
