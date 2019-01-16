#ifndef LIBGRAPHICS_LINE_H
#define LIBGRAPHICS_LINE_H

#include <cmath>
#include "Point.h"

struct Line {
    double m{0}, b{0};

    Line();
    explicit Line(int);
    Line(int, int);
    Line(const Line &);
    Line(Line &&) noexcept;
    virtual ~Line();

    double y(double x);
    Point point(int x);
};

#endif
