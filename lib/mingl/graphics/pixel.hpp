#ifndef MINGL_PIXEL_INCLUDED
#define MINGL_PIXEL_INCLUDED

#include "Colors/colors.hpp"
#include "Geometry/geometry.hpp"

class Pixel {
    Point p;
    RGBColor c;

public:
    Pixel(Point p, RGBColor c);
    virtual ~Pixel();
};

#endif
