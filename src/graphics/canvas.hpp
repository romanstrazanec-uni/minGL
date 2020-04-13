#ifndef MINGL_CANVAS_INCLUDED
#define MINGL_CANVAS_INCLUDED

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

    void setPixel(uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue);
    bool write(const char *filename) const;
    uint8_t *getData() const;
    uint8_t *getPixels() const;
};

#endif
