#ifndef MINGL_CANVAS_INCLUDED
#define MINGL_CANVAS_INCLUDED

#include "bitmap.hpp"

#include <windows.h>
#include <gdiplus.h>

#include <functional>

class Window;

class Canvas {
    Window *window;
    BitMap bitmap;

    HDC deviceContext{};
    PAINTSTRUCT paintStruct{};

    std::function<void(Gdiplus::Graphics *)> onDraw{[](Gdiplus::Graphics *) {}};
public:
    Canvas(Window *);

    void addOnDrawListener(std::function<void(Gdiplus::Graphics *)> &&);
    void removeOnDrawListener();
};

#endif
