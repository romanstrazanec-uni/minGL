#ifndef LIBGRAPHICS_CIRCLE_H
#define LIBGRAPHICS_CIRCLE_H

#include "Point.h"

struct Circle {
    Point c{Point()};
    unsigned int r{0};

    Circle();
    explicit Circle(unsigned int r);
    Circle(const Point &c, unsigned int r);
    Circle(int x, int y, unsigned int r);
    virtual ~Circle();

    bool is_point();
    void move_to(const Point &);
    void move_to(int x, int y);

    // comparision operators
    bool operator==(const Circle &) const;
    bool operator!=(const Circle &) const;
};

#endif
