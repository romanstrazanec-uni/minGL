#include "HSBColor.h"

HSBColor::HSBColor() = default;
HSBColor::HSBColor(unsigned short hue, float saturation, float brightness) {
    this->hue = (unsigned short) fminf(hue, 360);
    this->saturation = fminf(fabsf(saturation), 100);
    this->brightness = fminf(fabsf(brightness), 100);
}
HSBColor::HSBColor(const HSBColor &) = default;
HSBColor::~HSBColor() = default;
