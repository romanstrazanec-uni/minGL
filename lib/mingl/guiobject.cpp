#include "guiobject.hpp"
#include "window.hpp"

GUIObject::GUIObject(const char *className, long id, const char *name, int x, int y, int width, int height)
        : GUIObject(nullptr, className, id, name, x, y, width, height) {}

GUIObject::GUIObject(Window *parentWindow, const char *className, long id, const char *name, int x, int y,
                     int width, int height)
        : parentWindow(parentWindow), className(className), id(id), name(name), style(WS_VISIBLE), x(x), y(y),
          width(width), height(height) {
    if (parentWindow != nullptr) style |= WS_CHILD;
}

bool GUIObject::create() {
    if (isCreated()) return false;
    hwnd =
#ifdef USE_WNDCLASSEX
            CreateWindowEx(extendedStyle,
#else
            CreateWindow(
#endif
                    className, name, style,
x, y, width, height, parentWindow->getWindowHandle(), (HMENU) id, nullptr, nullptr);
    return isCreated();
}

int GUIObject::getX() const {
    return x;
}

int GUIObject::getY() const {
    return y;
}

int GUIObject::getWidth() const {
    return width;
}

int GUIObject::getHeight() const {
    return height;
}

long GUIObject::getId() const {
    return id;
}

bool GUIObject::isCreated() const {
    return hwnd != nullptr;
}
