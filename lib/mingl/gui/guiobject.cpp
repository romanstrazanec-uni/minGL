#include "guiobject.hpp"
#include "window.hpp"

GUIObject::GUIObject(const char *className, const char *name, int x, int y, int width, int height,
                     HINSTANCE hinstance, LPVOID additionalData)
        : className(className), name(name), x(x), y(y), width(width), height(height), hinstance(hinstance),
          additionalData(additionalData) {}

GUIObject::GUIObject(Window *parent, const char *className, long id, const char *name, int x, int y, int width,
                     int height) : className(className), id(id), name(name), x(x), y(y), width(width), height(height) {
    if (parent != nullptr) {
        addStyle(WS_CHILD);
        parent->addObject(this);
    }
}

bool GUIObject::create() {
    if (isCreated()) return true;
    hwnd =
#ifdef USE_WNDCLASSEX
            CreateWindowEx(extendedStyle,
#else
            CreateWindow(
#endif
                    className, name, style,
x, y, width, height, parent != nullptr ? parent->getWindowHandle() : nullptr,
hMenu, hinstance, additionalData);
    return isCreated();
}

void GUIObject::addStyle(UINT s) {
    style |= s;
}

const char *GUIObject::getClassName() const {
    return className;
}

const char *GUIObject::getName() const {
    return name;
}

HINSTANCE GUIObject::getHinstance() const {
    return hinstance;
}

LPVOID GUIObject::getAdditionalData() const {
    return additionalData;
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

HWND GUIObject::getWindowHandle() const {
    return hwnd;
}

bool GUIObject::isCreated() const {
    return hwnd != nullptr;
}

void GUIObject::setWindowHandle(HWND h) {
    hwnd = h;
}

void GUIObject::setParent(Window *window) {
    if (parent != nullptr) parent->remove(this);
    parent = window;
    if (parent != nullptr) addStyle(WS_CHILD);
}

void GUIObject::setName(const char *n) {
    name = n;
}
