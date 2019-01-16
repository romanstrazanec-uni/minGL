#ifndef LIBGRAPHICS_COLOR_H
#define LIBGRAPHICS_COLOR_H

#include <cstdint>

struct RGBColor {
    uint8_t r{0}, g{0}, b{0};

    RGBColor(uint8_t r, uint8_t g, uint8_t b);
    RGBColor(const RGBColor &);
    virtual ~RGBColor();

    void set_color(uint8_t r, uint8_t g, uint8_t b);
    void inverse();

    // assignment operators
    RGBColor& operator=(const RGBColor &);
    RGBColor& operator+=(const RGBColor &);
    RGBColor& operator-=(const RGBColor &);
    RGBColor& operator*=(const RGBColor &);
    RGBColor& operator/=(const RGBColor &);
    RGBColor& operator+=(uint8_t);
    RGBColor& operator-=(uint8_t);
    RGBColor& operator*=(uint8_t);
    RGBColor& operator/=(uint8_t);

    // arithmetic operators
    RGBColor operator+(const RGBColor &) const;
    RGBColor operator-(const RGBColor &) const;
    RGBColor operator*(const RGBColor &) const;
    RGBColor operator/(const RGBColor &) const;
    friend RGBColor operator+(RGBColor, uint8_t);
    friend RGBColor operator-(RGBColor, uint8_t);
    friend RGBColor operator*(RGBColor, uint8_t);
    friend RGBColor operator/(RGBColor, uint8_t);
    friend RGBColor operator+(uint8_t, RGBColor);
    friend RGBColor operator-(uint8_t, RGBColor);
    friend RGBColor operator*(uint8_t, RGBColor);
    friend RGBColor operator/(uint8_t, RGBColor);

    RGBColor operator-() const;

    // in/decrement operators
    RGBColor& operator++();
    RGBColor& operator--();
    const RGBColor operator++(int);
    const RGBColor operator--(int);

    // comparision operators
    bool operator==(const RGBColor &);
    bool operator!=(const RGBColor &);
};

#endif
