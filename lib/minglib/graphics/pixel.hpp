#ifndef MINGL_PIXEL_INCLUDED
#define MINGL_PIXEL_INCLUDED

#include "colors/colors.hpp"
#include "geometry/geometry.hpp"

class Pixel {
    Point p;
    RGBColor c;

public:
    Pixel(Point p, RGBColor c);
    virtual ~Pixel();
};

#endif
