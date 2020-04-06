#include "pixel.hpp"

Pixel::Pixel(const Point &p, const RGBColor &c) : point(p), color(c) {}
Pixel::Pixel(UINT16 x, UINT16 y, const RGBColor &c) : point(x, y), color(c) {}
Pixel::Pixel(const Point &p, UINT8 r, UINT8 g, UINT8 b) : point(p), color(r, g, b) {}
Pixel::Pixel(UINT16 x, UINT16 y, UINT8 r, UINT8 g, UINT8 b) : point(x, y), color(r, g, b) {}
Pixel::~Pixel() = default;
