#ifndef MINGL_PIXEL_INCLUDED
#define MINGL_PIXEL_INCLUDED

#include <windows.h>

#include "colors/colors.hpp"
#include "geometry/geometry.hpp"

struct Pixel {
    Point point;
    RGBColor color;

public:
    Pixel(const Point &, const RGBColor &);
    Pixel(UINT16 x, UINT16 y, const RGBColor &);
    Pixel(const Point &, UINT8 r, UINT8 g, UINT8 b);
    Pixel(UINT16 x, UINT16 y, UINT8 r, UINT8 g, UINT8 b);
    virtual ~Pixel();
};

#endif
