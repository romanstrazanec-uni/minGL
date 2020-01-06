#ifndef MINGL_CANVAS_INCLUDED
#define MINGL_CANVAS_INCLUDED

#include <windows.h>

#include <functional>
#include <memory>

class Window;

class Canvas {
    Window *window;

    HDC deviceContext{};
    PAINTSTRUCT paintStruct{};

    UINT pixelsSize{0};
    std::unique_ptr<UINT8[]> pixels{nullptr};

    bool updated{true};

public:
    Canvas(Window *);

    void setPixel(UINT16 x, UINT16 y, UINT8 red, UINT8 green, UINT8 blue);

    void forEachPixel(std::function<void(UINT)> &&);
};

#endif
