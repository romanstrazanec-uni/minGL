#include "RGBColor.h"

RGBColor::RGBColor(uint8_t red, uint8_t green, uint8_t blue): red(red), green(green), blue(blue) {}
RGBColor::RGBColor(const RGBColor &other) = default;
RGBColor::~RGBColor() = default;

void RGBColor::set_color(uint8_t red, uint8_t green, uint8_t blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}
void RGBColor::inverse() {
    *this = RGBColor(255, 255, 255) - *this;
}
HSLColor RGBColor::to_hsl(){
    float r = float(red)/256, g = float(green)/256, b = float(blue)/256;
    float max = fmaxf(fmaxf(r, g), b), min = fminf(fminf(r, g), b);
    short h = 0;
    if(max != min){
        auto fh = [](int n, float a, float b, float mx, float mn){
            return short(60 * (n + (a-b)/(mx - mn)));
        };
        if(max == r) h = fh(0, g, b, max, min);
        else if(max == g) h = fh(2, b, r, max, min);
        else h = fh(4, r, g, max, min);
    }
    float s = 0;
    if((max != 0)^(r != g != b != 0) && (min != 1)^(r != g != b != 1))
        s = (max-min)/(1-fabsf(max+min-1));
    return HSLColor(h < 0 ? h + short(360) : h, s, (max + min) / 2);
}

// assignment operators
RGBColor& RGBColor::operator=(const RGBColor &other) {
    red = other.red, green = other.green, blue = other.blue;
    return *this;
}
RGBColor& RGBColor::operator+=(const RGBColor &other) {
    if(red + other.red < 255) red += other.red;
    else red = 255;
    if(green + other.green < 255) green += other.green;
    else green = 255;
    if(blue + other.blue < 255) blue += other.blue;
    else blue = 255;
    return *this;
}
RGBColor& RGBColor::operator-=(const RGBColor &other) {
    if(red - other.red > 0) red -= other.red;
    else red = 0;
    if(green - other.green > 0) green -= other.green;
    else green = 0;
    if(blue - other.blue > 0) blue -= other.blue;
    else blue = 0;
    return *this;
}
RGBColor& RGBColor::operator*=(const RGBColor &other) {
    if(red * other.red <= 255) red *= other.red;
    else red = 255;
    if(green * other.green <= 255) green *= other.green;
    else green = 255;
    if(blue * other.blue <= 255) blue *= other.blue;
    else blue = 255;
    return *this;
}
RGBColor& RGBColor::operator/=(const RGBColor &other) {
    red /= other.red, green /= other.green, blue /= other.blue;
    return *this;
}
RGBColor& RGBColor::operator+=(uint8_t n) {
    if(red + n < 255) red += n;
    else red = 255;
    if(green + n < 255) green += n;
    else green = 255;
    if(blue + n < 255) blue += n;
    else blue = 255;
    return *this;
}
RGBColor& RGBColor::operator-=(uint8_t n) {
    if(red - n > 0) red -= n;
    else red = 0;
    if(green - n > 0) green -= n;
    else green = 0;
    if(blue - n > 0) blue -= n;
    else blue = 0;
    return *this;
}
RGBColor& RGBColor::operator*=(uint8_t n) {
    if(red * n < 255) red *= n;
    else red = 255;
    if(green * n < 255) green *= n;
    else green = 255;
    if(blue * n < 255) blue *= n;
    else blue = 255;
    return *this;
}
RGBColor& RGBColor::operator/=(uint8_t n) {
    red /= n, green /= n, blue /= n;
    return *this;
}

// arithmetic operators
RGBColor RGBColor::operator+(const RGBColor &other) const {
    uint8_t nr = red, ng = green, nb = blue;
    if(red + other.red < 255) nr += other.red;
    else nr = 255;
    if(green + other.green < 255) ng += other.green;
    else ng = 255;
    if(blue + other.blue < 255) nb += other.blue;
    else nb = 255;
    return RGBColor(nr, ng, nb);
}
RGBColor RGBColor::operator-(const RGBColor &other) const {
    uint8_t nr = red, ng = green, nb = blue;
    if(red - other.red > 0) nr -= other.red;
    else nr = 0;
    if(green - other.green > 0) ng -= other.green;
    else ng = 0;
    if(blue - other.blue > 0) nb -= other.blue;
    else nb = 0;
    return RGBColor(nr, ng, nb);
}
RGBColor RGBColor::operator*(const RGBColor &other) const {
    uint8_t nr = red, ng = green, nb = blue;
    if(red * other.red <= 255) nr *= other.red;
    else nr = 255;
    if(green * other.green <= 255) ng *= other.green;
    else ng = 255;
    if(blue * other.blue <= 255) nb *= other.blue;
    else nb = 255;
    return RGBColor(nr, ng, nb);
}
RGBColor RGBColor::operator/(const RGBColor &other) const {
    return RGBColor(red / other.red, green / other.green, blue / other.blue);
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
    if(red < 255) ++red;
    if(green < 255) ++green;
    if(blue < 255) ++blue;
    return *this;
}
RGBColor& RGBColor::operator--(){
    if(red > 0) --red;
    if(green > 0) --green;
    if(blue > 0) --blue;
    return *this;
}
const RGBColor RGBColor::operator++(int){
    if(red < 255) red++;
    if(green < 255) green++;
    if(blue < 255) blue++;
    return *this;
}
const RGBColor RGBColor::operator--(int){
    if(red > 0) red--;
    if(green > 0) green--;
    if(blue > 0) blue--;
    return *this;
}

// comparision operators
bool RGBColor::operator==(const RGBColor &other) {
    return red == other.red && green == other.green && blue == other.blue;
}
bool RGBColor::operator!=(const RGBColor &other) {
    return !(*this == other);
}
