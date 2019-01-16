#ifndef LIBGRAPHICS_HSVCOLOR_H
#define LIBGRAPHICS_HSVCOLOR_H

#include <cmath>

struct HSBColor {
    unsigned short hue{0};
    float saturation{0}, brightness{0};

    HSBColor();
    HSBColor(unsigned short hue, float saturation, float brightness);
    HSBColor(const HSBColor &);
    virtual ~HSBColor();
};

#endif
