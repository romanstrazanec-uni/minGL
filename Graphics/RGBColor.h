#ifndef LIBGRAPHICS_COLOR_H
#define LIBGRAPHICS_COLOR_H

#include <cstdint>

struct RGBColor {
    uint8_t r{0}, g{0}, b{0};

    // constructors
    RGBColor(uint8_t r, uint8_t g, uint8_t b);
    RGBColor(const RGBColor &);
    RGBColor(RGBColor &&) noexcept;
    virtual ~RGBColor();

    void set_color(uint8_t r, uint8_t g, uint8_t b);

    // assignment operators
    RGBColor& operator=(const RGBColor &); // copy assignment
    RGBColor& operator=(RGBColor &&) noexcept; // move assignment

    // assignment arithmetic operators
    RGBColor& operator+=(const RGBColor &);
    RGBColor& operator-=(const RGBColor &);
    RGBColor& operator*=(const RGBColor &);
    RGBColor& operator/=(const RGBColor &);
    RGBColor& operator+=(uint8_t);
    RGBColor& operator-=(uint8_t);
    RGBColor& operator*=(uint8_t);
    RGBColor& operator/=(uint8_t);

    // arithmetic operators
    friend RGBColor operator+(RGBColor, uint8_t);
    friend RGBColor operator-(RGBColor, uint8_t);
    friend RGBColor operator*(RGBColor, uint8_t);
    friend RGBColor operator/(RGBColor, uint8_t);
    friend RGBColor operator+(uint8_t, RGBColor);
    friend RGBColor operator-(uint8_t, RGBColor);
    friend RGBColor operator*(uint8_t, RGBColor);
    friend RGBColor operator/(uint8_t, RGBColor);

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
