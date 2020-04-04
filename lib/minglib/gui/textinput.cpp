#include "textinput.hpp"

#include "font.hpp"

TextInput::TextInput(long id, UINT16 x, UINT16 y)
        : TextInput(nullptr, id, x, y) {}
TextInput::TextInput(long id, const char *text, UINT16 x, UINT16 y)
        : TextInput(nullptr, id, text, x, y) {}
TextInput::TextInput(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : TextInput(id, "", x, y, width, height) {}
TextInput::TextInput(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : TextInput(nullptr, id, text, x, y, width, height) {}
TextInput::TextInput(Window *parent, long id, UINT16 x, UINT16 y)
        : TextInput(parent, id, "", x, y) {}
TextInput::TextInput(Window *parent, long id, const char *text, UINT16 x, UINT16 y)
        : TextInput(parent, id, text, x, y, 0, 0) {}
TextInput::TextInput(Window *parent, long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : TextInput(parent, id, "", x, y, width, height) {}
TextInput::TextInput(Window *parent, long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : GUIObject(parent, "Edit", id, text, x, y, width, height) {}

void TextInput::computeSize() {
    unsigned short minWidth = FONT_WIDTH * getText().length();
    if (getWidth() < minWidth) setWidth(minWidth);
    if (getHeight() < FONT_HEIGHT) setHeight(FONT_HEIGHT);
}

void TextInput::addBorder() {
    addStyle(WS_BORDER);
}
