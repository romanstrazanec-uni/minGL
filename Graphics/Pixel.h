#ifndef LIBGRAPHICS_PIXEL_H
#define LIBGRAPHICS_PIXEL_H

#include "Colors/colors.h"
#include "Geometry/geometry.h"

class Pixel {
    Point p;
    RGBColor c;

public:
    Pixel(Point p, RGBColor c);
    virtual ~Pixel();
};


#endif
