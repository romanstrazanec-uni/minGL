#include "RGBColor.h"

// constructors
RGBColor::RGBColor(uint8_t r, uint8_t g, uint8_t b): r(r), g(g), b(b) {}
RGBColor::RGBColor(const RGBColor &other) = default;
RGBColor::RGBColor(RGBColor &&) noexcept = default;
RGBColor::~RGBColor() = default;

void RGBColor::set_color(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->r = r;
}

// assignment operators
RGBColor& RGBColor::operator=(const RGBColor &other) {
    r = other.r, g = other.g, b = other.b;
    return *this;
}
RGBColor& RGBColor::operator=(RGBColor &&other) noexcept {
    r = other.r, g = other.g, b = other.b;
    return *this;
}

// arithmetic assignment operators
RGBColor& RGBColor::operator+=(const RGBColor &other) {
    if(r + other.r < 255) r += other.r;
    else r = 255;
    if(g + other.g < 255) g += other.g;
    else g = 255;
    if(b + other.b < 255) b += other.b;
    else b = 255;
    return *this;
}
RGBColor& RGBColor::operator-=(const RGBColor &other) {
    if(r - other.r > 0) r -= other.r;
    else r = 0;
    if(g - other.g > 0) g -= other.g;
    else g = 0;
    if(b - other.b > 0) b -= other.b;
    else b = 0;
    return *this;
}
RGBColor& RGBColor::operator*=(const RGBColor &other) {
    if(r * other.r <= 255) r *= other.r;
    else r = 255;
    if(g * other.g <= 255) g *= other.g;
    else g = 255;
    if(b * other.b <= 255) b *= other.b;
    else b = 255;
    return *this;
}
RGBColor& RGBColor::operator/=(const RGBColor &other) {
    r /= other.r, g /= other.g, b /= other.b;
    return *this;
}
RGBColor& RGBColor::operator+=(uint8_t n) {
    if(r + n < 255) r += n;
    else r = 255;
    if(g + n < 255) g += n;
    else g = 255;
    if(b + n < 255) b += n;
    else b = 255;
    return *this;
}
RGBColor& RGBColor::operator-=(uint8_t n) {
    if(r - n > 0) r += n;
    else r = 0;
    if(g - n > 0) g += n;
    else g = 0;
    if(b - n > 0) b += n;
    else b = 0;
    return *this;
}
RGBColor& RGBColor::operator*=(uint8_t n) {
    if(r * n < 255) r *= n;
    else r = 255;
    if(g * n < 255) g *= n;
    else g = 255;
    if(b * n < 255) b *= n;
    else b = 255;
    return *this;
}
RGBColor& RGBColor::operator/=(uint8_t n) {
    r /= n, g /= n, b /= n;
    return *this;
}

// arithmetic operators
RGBColor operator+(RGBColor rgb, uint8_t n){ return rgb += n; }
RGBColor operator-(RGBColor rgb, uint8_t n){ return rgb -= n; }
RGBColor operator*(RGBColor rgb, uint8_t n){ return rgb *= n; }
RGBColor operator/(RGBColor rgb, uint8_t n){ return rgb /= n; }
RGBColor operator+(uint8_t n, RGBColor rgb){ return rgb += n; }
RGBColor operator-(uint8_t n, RGBColor rgb){ return rgb -= n; }
RGBColor operator*(uint8_t n, RGBColor rgb){ return rgb *= n; }
RGBColor operator/(uint8_t n, RGBColor rgb){ return rgb /= n; }

// in/decrement operators
RGBColor& RGBColor::operator++(){
    if(r < 255) ++r;
    if(g < 255) ++g;
    if(b < 255) ++b;
    return *this;
}
RGBColor& RGBColor::operator--(){
    if(r > 0) --r;
    if(g > 0) --g;
    if(b > 0) --b;
    return *this;
}
const RGBColor RGBColor::operator++(int){
    if(r < 255) r++;
    if(g < 255) g++;
    if(b < 255) b++;
    return *this;
}
const RGBColor RGBColor::operator--(int){
    if(r > 0) r--;
    if(g > 0) g--;
    if(b > 0) b--;
    return *this;
}

// comparision operators
bool RGBColor::operator==(const RGBColor &other) {
    return r == other.r && g == other.g && b == other.b;
}
bool RGBColor::operator!=(const RGBColor &other) {
    return !(*this == other);
}

