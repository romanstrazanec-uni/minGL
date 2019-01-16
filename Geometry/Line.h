#ifndef LIBGRAPHICS_LINE_H
#define LIBGRAPHICS_LINE_H

#include <cmath>
#include "Point.h"
#include "LineSegment.h"

struct Line {
    double m{0}, b{0};

    Line();
    explicit Line(double slope);
    Line(double slope, double b);
    Line(const Line &);
    virtual ~Line();

    double y(double x);
    Point point(int x);
    LineSegment segment(int startx, int endx);
};

#endif
