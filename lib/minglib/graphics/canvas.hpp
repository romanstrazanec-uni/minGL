#ifndef MINGL_CANVAS_INCLUDED
#define MINGL_CANVAS_INCLUDED

#include <windows.h>

#include <functional>
#include <memory>

class Window;

class Canvas {
    HDC deviceContext{};
    PAINTSTRUCT paintStruct{};

    UINT pixelsSize{0};
    std::unique_ptr<UINT8[]> pixels{nullptr};

    bool updated{true};

public:
    Canvas(Window *);
};

#endif
