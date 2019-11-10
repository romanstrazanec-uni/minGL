#include "button.hpp"
#include "window.hpp"

Button::Button(Window *window, long id, const char *title, int x, int y, int width, int height)
        : Button(window, id, title, x, y, width, height, nullptr) {}

Button::Button(Window *window, long id, const char *title, int x, int y, int width, int height, void (*onClick)())
        : onClick(onClick), GUIObject(window, "Button", id, title, x, y, width, height) {}

void Button::addOnClickListener(void (*onClickListener)()) {
    onClick = onClickListener;
}

void Button::performClick() {
    if (onClick != nullptr) onClick();
}

const char *Button::getTitle() const {
    return name;
}
