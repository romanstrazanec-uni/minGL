#include "rgbcolor.hpp"

RGBColor::RGBColor(UINT8 red, UINT8 green, UINT8 blue) : red(red), green(green), blue(blue) {}
RGBColor::RGBColor(const RGBColor &other) = default;
RGBColor::~RGBColor() = default;

void RGBColor::setColor(UINT8 r, UINT8 g, UINT8 b) {
    red = r, green = g, blue = b;
}

void RGBColor::inverse() {
    *this = RGBColor(255, 255, 255) - *this;
}

HSLColor RGBColor::toHSL() {
    float r = float(red) / 256, g = float(green) / 256, b = float(blue) / 256;
    float max = fmaxf(fmaxf(r, g), b), min = fminf(fminf(r, g), b);
    short h = 0;
    if (max != min) {
        auto fh = [](int n, float a, float b, float mx, float mn) {
            return short(60 * (n + (a - b) / (mx - mn)));
        };
        if (max == r) h = fh(0, g, b, max, min);
        else if (max == g) h = fh(2, b, r, max, min);
        else h = fh(4, r, g, max, min);
    }
    float s = 0;
    if ((max != 0) ^ ((r != g) && (g != b) && (b != 0)) && (min != 1) ^ ((r != g) && (g != b) && (b != 1)))
        s = (max - min) / (1 - fabsf(max + min - 1));
    return HSLColor(static_cast<short>(h < 0 ? h + 360 : h), s, (max + min) / 2);
}

/* Assignment operators */
RGBColor &RGBColor::operator=(const RGBColor &other) {
    red = other.red, green = other.green, blue = other.blue;
    return *this;
}

RGBColor &RGBColor::operator+=(const RGBColor &other) {
    if (red + other.red < 255) red += other.red;
    else red = 255;
    if (green + other.green < 255) green += other.green;
    else green = 255;
    if (blue + other.blue < 255) blue += other.blue;
    else blue = 255;
    return *this;
}

RGBColor &RGBColor::operator-=(const RGBColor &other) {
    if (red - other.red > 0) red -= other.red;
    else red = 0;
    if (green - other.green > 0) green -= other.green;
    else green = 0;
    if (blue - other.blue > 0) blue -= other.blue;
    else blue = 0;
    return *this;
}

RGBColor &RGBColor::operator*=(const RGBColor &other) {
    if (red * other.red <= 255) red *= other.red;
    else red = 255;
    if (green * other.green <= 255) green *= other.green;
    else green = 255;
    if (blue * other.blue <= 255) blue *= other.blue;
    else blue = 255;
    return *this;
}

RGBColor &RGBColor::operator/=(const RGBColor &other) {
    red /= other.red, green /= other.green, blue /= other.blue;
    return *this;
}

RGBColor &RGBColor::operator+=(UINT8 n) {
    if (red + n < 255) red += n;
    else red = 255;
    if (green + n < 255) green += n;
    else green = 255;
    if (blue + n < 255) blue += n;
    else blue = 255;
    return *this;
}

RGBColor &RGBColor::operator-=(UINT8 n) {
    if (red - n > 0) red -= n;
    else red = 0;
    if (green - n > 0) green -= n;
    else green = 0;
    if (blue - n > 0) blue -= n;
    else blue = 0;
    return *this;
}

RGBColor &RGBColor::operator*=(UINT8 n) {
    if (red * n < 255) red *= n;
    else red = 255;
    if (green * n < 255) green *= n;
    else green = 255;
    if (blue * n < 255) blue *= n;
    else blue = 255;
    return *this;
}

RGBColor &RGBColor::operator/=(UINT8 n) {
    red /= n, green /= n, blue /= n;
    return *this;
}

/* Arithmetic operators */
RGBColor RGBColor::operator+(const RGBColor &other) const {
    UINT8 nr = red, ng = green, nb = blue;
    if (red + other.red < 255) nr += other.red;
    else nr = 255;
    if (green + other.green < 255) ng += other.green;
    else ng = 255;
    if (blue + other.blue < 255) nb += other.blue;
    else nb = 255;
    return RGBColor(nr, ng, nb);
}

RGBColor RGBColor::operator-(const RGBColor &other) const {
    UINT8 nr = red, ng = green, nb = blue;
    if (red - other.red > 0) nr -= other.red;
    else nr = 0;
    if (green - other.green > 0) ng -= other.green;
    else ng = 0;
    if (blue - other.blue > 0) nb -= other.blue;
    else nb = 0;
    return RGBColor(nr, ng, nb);
}

RGBColor RGBColor::operator*(const RGBColor &other) const {
    UINT8 nr = red, ng = green, nb = blue;
    if (red * other.red <= 255) nr *= other.red;
    else nr = 255;
    if (green * other.green <= 255) ng *= other.green;
    else ng = 255;
    if (blue * other.blue <= 255) nb *= other.blue;
    else nb = 255;
    return RGBColor(nr, ng, nb);
}

RGBColor RGBColor::operator/(const RGBColor &other) const {
    return RGBColor(red / other.red, green / other.green, blue / other.blue);
}

RGBColor operator+(RGBColor rgb, UINT8 n) { return rgb += n; }
RGBColor operator-(RGBColor rgb, UINT8 n) { return rgb -= n; }
RGBColor operator*(RGBColor rgb, UINT8 n) { return rgb *= n; }
RGBColor operator/(RGBColor rgb, UINT8 n) { return rgb /= n; }
RGBColor operator+(UINT8 n, RGBColor rgb) { return rgb += n; }
RGBColor operator-(UINT8 n, RGBColor rgb) { return rgb -= n; }
RGBColor operator*(UINT8 n, RGBColor rgb) { return rgb *= n; }
RGBColor operator/(UINT8 n, RGBColor rgb) { return rgb /= n; }

RGBColor RGBColor::operator-() const {
    return RGBColor(255, 255, 255) - *this;
}

/* In/decrement operators */
RGBColor &RGBColor::operator++() {
    if (red < 255) ++red;
    if (green < 255) ++green;
    if (blue < 255) ++blue;
    return *this;
}

RGBColor &RGBColor::operator--() {
    if (red > 0) --red;
    if (green > 0) --green;
    if (blue > 0) --blue;
    return *this;
}

const RGBColor &RGBColor::operator++(int) {
    if (red < 255) red++;
    if (green < 255) green++;
    if (blue < 255) blue++;
    return *this;
}

const RGBColor &RGBColor::operator--(int) {
    if (red > 0) red--;
    if (green > 0) green--;
    if (blue > 0) blue--;
    return *this;
}

/* Comparision operators */
bool RGBColor::operator==(const RGBColor &other) {
    return red == other.red && green == other.green && blue == other.blue;
}

bool RGBColor::operator!=(const RGBColor &other) {
    return !(*this == other);
}
