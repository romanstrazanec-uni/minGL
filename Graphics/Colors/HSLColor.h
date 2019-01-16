#ifndef LIBGRAPHICS_HSLCOLOR_H
#define LIBGRAPHICS_HSLCOLOR_H

#include <cmath>
#include "RGBColor.h"

struct HSLColor {
    short hue{-1};
    float saturation{0}, lightness{0};

    HSLColor();
    HSLColor(short hue, float saturation, float lightness);
    HSLColor(const HSLColor &);
    virtual ~HSLColor();

    float chroma() const;
    RGBColor to_rgb();
};

#endif
