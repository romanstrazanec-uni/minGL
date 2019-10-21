#ifndef MINGL_LINE_HPP_INCLUDED
#define MINGL_LINE_HPP_INCLUDED

#include <cmath>
#include "geometry.hpp"

struct Line {
    double m{0}, b{0};

    Line();
    explicit Line(double slope);
    Line(double slope, double b);
    Line(const Line &);
    virtual ~Line();

    double y(double x);
    Point point(int x);
    Edge segment(int startx, int endx);
};

#endif
