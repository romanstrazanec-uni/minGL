#include "button.hpp"
#include "window.hpp"
#include "font.hpp"

Button::Button(long id, const char *title, UINT16 x, UINT16 y, OnClickHandle onClick)
        : Button(nullptr, id, title, x, y, std::move(onClick)) {}
Button::Button(long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height, OnClickHandle onClick)
        : Button(nullptr, id, title, x, y, width, height, std::move(onClick)) {}
Button::Button(Window *window, long id, const char *title, UINT16 x, UINT16 y, OnClickHandle onClick)
        : Button(window, id, title, x, y, 0, 0, std::move(onClick)) {}
Button::Button(Window *window, long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height,
               OnClickHandle onClick)
        : onClick(std::move(onClick)), GUIObject(window, "Button", id, title, x, y, width, height) {
    hMenu = (HMENU) id;
}

void Button::addOnClickListener(OnClickHandle onClickListener) {
    onClick = std::move(onClickListener);
}

void Button::removeOnClickListener() {
    addOnClickListener(nullptr);
}

void Button::performClick() {
    if (isCreated() && onClick != nullptr) onClick();
}

const char *Button::getTitle() const {
    return getName();
}

void Button::computeSize() {
    unsigned long length = static_cast<unsigned long>(getText().length());
    if (length > 0) {
        auto minWidth = static_cast<unsigned short>(FONT_WIDTH * length);
        if (getWidth() < minWidth) setWidth(minWidth);
        if (getHeight() < FONT_HEIGHT) setHeight(FONT_HEIGHT);
    }
}
