#ifndef MINGL_CANVAS_INCLUDED
#define MINGL_CANVAS_INCLUDED

#include "colors/colors.hpp"

#include <windows.h>
#include <gdiplus.h>

#include <functional>
#include <memory>

class Window;

typedef std::function<void(Gdiplus::Graphics *)> OnDrawHandle;

/**
 * Canvas for window.
 */
class Canvas final {
    Window *window;
    UINT16 width;
    UINT16 height;

    /**
     * Bitmap data.
     */
    std::unique_ptr<uint8_t[]> data;

    OnDrawHandle onDraw{[](Gdiplus::Graphics *) {}};

public:
    /**
     * Cannot be created without window.
     */
    Canvas() = delete;

    /**
     * Cannot be copied.
     */
    Canvas(const Canvas &) = delete;

    /**
     * Create in the window.
     */
    explicit Canvas(Window *);
    ~Canvas();

    void addOnDrawListener(OnDrawHandle &&);
    void removeOnDrawListener();

    void setPixel(UINT16 x, UINT16 y, const RGBColor &);
    void drawArea(UINT16 x, UINT16 y, UINT16 width, UINT16 height, const RGBColor &);

    /**
     * Write bitmap data to file.
     *
     * @returns true if writing successful.
     */
    bool write(const char *filename) const;
    uint8_t *getData() const;
    uint8_t *getPixels() const;
};

#endif
