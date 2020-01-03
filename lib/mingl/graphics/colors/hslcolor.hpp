#ifndef MINGL_HSLCOLOR_INCLUDED
#define MINGL_HSLCOLOR_INCLUDED

#include <cmath>
#include <mingl/graphics/colors/colors.hpp>

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
