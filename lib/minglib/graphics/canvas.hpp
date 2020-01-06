#ifndef MINGL_CANVAS_INCLUDED
#define MINGL_CANVAS_INCLUDED

#include "../gui/window.hpp"

#include <windef.h>
#include <winuser.h>
#include <gdiplus.h>

#include <functional>
#include <memory>

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
