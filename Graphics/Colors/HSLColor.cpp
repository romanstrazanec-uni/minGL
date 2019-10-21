#include "HSLColor.hpp"

HSLColor::HSLColor() = default;
HSLColor::HSLColor(short hue, float saturation, float lightness) {
    this->hue = (unsigned short) fminf(hue, 360);
    this->saturation = fminf(fabsf(saturation), 100);
    this->lightness = fminf(fabsf(lightness), 100);
}
HSLColor::HSLColor(const HSLColor &) = default;
HSLColor::~HSLColor() = default;

float HSLColor::chroma() const { return (1 - fabsf(2*(lightness/100) - 1)) * saturation/100; }

RGBColor HSLColor::to_rgb() {
    double l = lightness*.01;
    double a = saturation*.01 * fmin(l, 1 - l);
    auto f = [](int n, short h, double a, double l){
        return (uint8_t)(l - a * fmax(fmin(fmin((n + h/30) % 12 - 3, 9 - (n + h/30) % 12), 1), -1));
    };
    return RGBColor(f(0, hue, a, l), f(8, hue, a, l), f(4, hue, a, l));
}
