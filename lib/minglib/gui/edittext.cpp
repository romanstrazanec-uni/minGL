#include "edittext.hpp"

#include "font.hpp"

EditText::EditText(long id, UINT16 x, UINT16 y)
        : EditText(nullptr, id, x, y) {}
EditText::EditText(long id, const char *text, UINT16 x, UINT16 y)
        : EditText(nullptr, id, text, x, y) {}
EditText::EditText(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : EditText(id, "", x, y, width, height) {}
EditText::EditText(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : EditText(nullptr, id, text, x, y, width, height) {}
EditText::EditText(Window *parent, long id, UINT16 x, UINT16 y)
        : EditText(parent, id, "", x, y) {}
EditText::EditText(Window *parent, long id, const char *text, UINT16 x, UINT16 y)
        : EditText(parent, id, text, x, y, 0, 0) {}
EditText::EditText(Window *parent, long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : EditText(parent, id, "", x, y, width, height) {}
EditText::EditText(Window *parent, long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : GUIObject(parent, "Edit", id, text, x, y, width, height) {}

void EditText::computeSize() {
    unsigned short minWidth = FONT_WIDTH * getText().length();
    if (getWidth() < minWidth) setWidth(minWidth);
    if (getHeight() < FONT_HEIGHT) setHeight(FONT_HEIGHT);
}