#include "RGBColor.h"

RGBColor::RGBColor(uint8_t r, uint8_t g, uint8_t b): r(r), g(g), b(b) {}
RGBColor::RGBColor(const RGBColor &other) = default;
RGBColor::~RGBColor() = default;

void RGBColor::set_color(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->r = r;
}
void RGBColor::inverse() {
    *this = RGBColor(255, 255, 255) - *this;
}

// assignment operators
RGBColor& RGBColor::operator=(const RGBColor &other) {
    r = other.r, g = other.g, b = other.b;
    return *this;
}
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
RGBColor RGBColor::operator+(const RGBColor &other) const {
    uint8_t nr = r, ng = g, nb = b;
    if(r + other.r < 255) nr += other.r;
    else nr = 255;
    if(g + other.g < 255) ng += other.g;
    else ng = 255;
    if(b + other.b < 255) nb += other.b;
    else nb = 255;
    return RGBColor(nr, ng, nb);
}
RGBColor RGBColor::operator-(const RGBColor &other) const {
    uint8_t nr = r, ng = g, nb = b;
    if(r - other.r > 0) nr -= other.r;
    else nr = 0;
    if(g - other.g > 0) ng -= other.g;
    else ng = 0;
    if(b - other.b > 0) nb -= other.b;
    else nb = 0;
    return RGBColor(nr, ng, nb);
}
RGBColor RGBColor::operator*(const RGBColor &other) const {
    uint8_t nr = r, ng = g, nb = b;
    if(r * other.r <= 255) nr *= other.r;
    else nr = 255;
    if(g * other.g <= 255) ng *= other.g;
    else ng = 255;
    if(b * other.b <= 255) nb *= other.b;
    else nb = 255;
    return RGBColor(nr, ng, nb);
}
RGBColor RGBColor::operator/(const RGBColor &other) const {
    return RGBColor(r / other.r, g / other.g, b / other.b);
}
RGBColor operator+(RGBColor rgb, uint8_t n){ return rgb += n; }
RGBColor operator-(RGBColor rgb, uint8_t n){ return rgb -= n; }
RGBColor operator*(RGBColor rgb, uint8_t n){ return rgb *= n; }
RGBColor operator/(RGBColor rgb, uint8_t n){ return rgb /= n; }
RGBColor operator+(uint8_t n, RGBColor rgb){ return rgb += n; }
RGBColor operator-(uint8_t n, RGBColor rgb){ return rgb -= n; }
RGBColor operator*(uint8_t n, RGBColor rgb){ return rgb *= n; }
RGBColor operator/(uint8_t n, RGBColor rgb){ return rgb /= n; }

RGBColor RGBColor::operator-() const {
    return RGBColor(255, 255, 255) - *this;
}

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
