#ifndef LIBGRAPHICS_CIRCLE_H
#define LIBGRAPHICS_CIRCLE_H

#include "Point.h"

struct Circle {
    Point c;
    unsigned int r;

    Circle();
    explicit Circle(unsigned int r);
    Circle(const Point &c, unsigned int r);
    Circle(int x, int y, unsigned int r);
    virtual ~Circle();

    bool is_point();
};

#endif
