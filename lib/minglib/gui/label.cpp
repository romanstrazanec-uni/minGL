#include "label.hpp"

#include "font.hpp"

Label::Label(long id, const char *text, UINT16 x, UINT16 y)
        : Label(nullptr, id, text, x, y) {}
Label::Label(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : Label(nullptr, id, text, x, y, width, height) {}
Label::Label(Window *parent, long id, const char *text, UINT16 x, UINT16 y)
        : Label(parent, id, text, x, y, 0, 0) {}
Label::Label(Window *parent, long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : GUIObject(parent, "Static", id, text, x, y, width, height) {}

void Label::computeSize() {
    unsigned long length = getText().length();
    if (length > 0) {
        unsigned short minWidth = FONT_WIDTH * length;
        if (getWidth() < minWidth) setWidth(minWidth);
        if (getHeight() < FONT_HEIGHT) setHeight(FONT_HEIGHT);
    }
}
