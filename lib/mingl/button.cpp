#include "button.hpp"
#include "window.hpp"

Button::Button(Window *window, long id, const char *title, int x, int y, int width, int height) : window(window),
                                                                                                  id(id),
                                                                                                  title(title),
                                                                                                  x(x), y(y),
                                                                                                  width(width),
                                                                                                  height(height) {}

Button::Button(Window *window, long id, const char *title, int x, int y, int width, int height, void (*onClick)())
        : window(window),
          id(id),
          title(title),
          x(x), y(y),
          width(width),
          height(height), onClick(onClick) {}

void Button::create() const {
#ifdef USE_WNDCLASSEX
    CreateWindowEx(extendedStyle,
#else
    CreateWindow(
#endif
            "Button", title, style,
x, y, width, height, window->getWindowHandle(), (HMENU) id, nullptr, nullptr);
}

void Button::addOnClickListener(void (*onClickListener)()) {
    onClick = onClickListener;
}

void Button::performClick() {
    if (onClick != nullptr) onClick();
}

long Button::getId() const {
    return id;

}

const char *Button::getTitle() const {
    return title;
}

int Button::getX() const {
    return x;
}

int Button::getY() const {
    return y;
}

int Button::getWidth() const {
    return width;
}

int Button::getHeight() const {
    return height;
}
