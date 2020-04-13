#ifndef MINGL_CANVAS_INCLUDED
#define MINGL_CANVAS_INCLUDED

#include "colors/colors.hpp"

#include <windows.h>
#include <gdiplus.h>

#include <functional>
#include <memory>

class Window;

class Canvas {
    Window *window;
    uint32_t width;
    uint32_t height;
    std::unique_ptr<uint8_t[]> data{nullptr};

    std::function<void(Gdiplus::Graphics *)> onDraw{[](Gdiplus::Graphics *) {}};

public:
    Canvas(Window *);
    virtual ~Canvas();

    void addOnDrawListener(std::function<void(Gdiplus::Graphics *)> &&);
    void removeOnDrawListener();

    void setPixel(uint32_t x, uint32_t y, const RGBColor &);
    void drawArea(uint32_t x, uint32_t y, uint32_t width, uint32_t height, const RGBColor &);
    bool write(const char *filename) const;
    uint8_t *getData() const;
    uint8_t *getPixels() const;
};

#endif
