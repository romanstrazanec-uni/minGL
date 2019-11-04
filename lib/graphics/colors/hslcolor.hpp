#ifndef MINGL_HSLCOLOR_HPP_INCLUDED
#define MINGL_HSLCOLOR_HPP_INCLUDED

#include <cmath>
#include "colors.hpp"

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
