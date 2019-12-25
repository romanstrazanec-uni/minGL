#include "button.hpp"
#include "window.hpp"

Button::Button(long id, const char *title, int x, int y, int width, int height)
        : Button(nullptr, id, title, x, y, width, height) {}

Button::Button(long id, const char *title, int x, int y, int width, int height, std::function<void()> onClick)
        : Button(nullptr, id, title, x, y, width, height, onClick) {}

Button::Button(Window *window, long id, const char *title, int x, int y, int width, int height)
        : Button(window, id, title, x, y, width, height, nullptr) {}

Button::Button(Window *window, long id, const char *title, int x, int y, int width, int height,
               std::function<void()> onClick)
        : onClick(onClick), GUIObject(window, "Button", id, title, x, y, width, height) {}

void Button::addOnClickListener(std::function<void()> onClickListener) {
    onClick = onClickListener;
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
