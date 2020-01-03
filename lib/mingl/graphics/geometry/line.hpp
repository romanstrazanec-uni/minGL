#ifndef MINGL_LINE_INCLUDED
#define MINGL_LINE_INCLUDED

#include <cmath>
#include <mingl/graphics/geometry/geometry.hpp>

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
