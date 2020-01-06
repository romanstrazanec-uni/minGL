#include "button.hpp"
#include "window.hpp"

Button::Button(long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : Button(nullptr, id, title, x, y, width, height) {}
Button::Button(long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height, void (*onClick)(Window *))
        : Button(nullptr, id, title, x, y, width, height, onClick) {}
Button::Button(Window *window, long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : Button(window, id, title, x, y, width, height, nullptr) {}
Button::Button(Window *window, long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height,
               void (*onClick)(Window *))
        : onClick(onClick), GUIObject(window, "Button", id, title, x, y, width, height) {
    hMenu = (HMENU) id;
}

void Button::addOnClickListener(void (*onClickListener)(Window *)) {
    onClick = onClickListener;
}

void Button::removeOnClickListener() {
    addOnClickListener(nullptr);
}

void Button::performClick() {
    if (isCreated() && onClick != nullptr) onClick(parent);
}

const char *Button::getTitle() const {
    return getName();
}
