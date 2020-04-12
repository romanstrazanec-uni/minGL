#ifndef MINGL_RGBCOLOR_INCLUDED
#define MINGL_RGBCOLOR_INCLUDED

#include <windows.h>

#include "colors.hpp"

struct RGBColor {
    UINT8 red{0}, green{0}, blue{0};

    RGBColor(UINT8 red, UINT8 green, UINT8 blue);
    RGBColor(const RGBColor &);
    virtual ~RGBColor();

    void setColor(UINT8 red, UINT8 green, UINT8 blue);
    void inverse();
    HSLColor toHSL();

    /* Assignment operators */
    RGBColor &operator=(const RGBColor &);
    RGBColor &operator+=(const RGBColor &);
    RGBColor &operator-=(const RGBColor &);
    RGBColor &operator*=(const RGBColor &);
    RGBColor &operator/=(const RGBColor &);
    RGBColor &operator+=(UINT8);
    RGBColor &operator-=(UINT8);
    RGBColor &operator*=(UINT8);
    RGBColor &operator/=(UINT8);

    /* Arithmetic operators */
    RGBColor operator+(const RGBColor &) const;
    RGBColor operator-(const RGBColor &) const;
    RGBColor operator*(const RGBColor &) const;
    RGBColor operator/(const RGBColor &) const;
    friend RGBColor operator+(RGBColor, UINT8);
    friend RGBColor operator-(RGBColor, UINT8);
    friend RGBColor operator*(RGBColor, UINT8);
    friend RGBColor operator/(RGBColor, UINT8);
    friend RGBColor operator+(UINT8, RGBColor);
    friend RGBColor operator-(UINT8, RGBColor);
    friend RGBColor operator*(UINT8, RGBColor);
    friend RGBColor operator/(UINT8, RGBColor);

    RGBColor operator-() const;

    /* In/decrement operators */
    RGBColor &operator++();
    RGBColor &operator--();
    const RGBColor &operator++(int);
    const RGBColor &operator--(int);

    /* Comparision operators */
    bool operator==(const RGBColor &);
    bool operator!=(const RGBColor &);
};

#endif
