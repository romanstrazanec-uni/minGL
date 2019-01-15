#ifndef LIBGRAPHICS_LINE_H
#define LIBGRAPHICS_LINE_H

#include <cmath>
#include "Point.h"

struct Line {
    Point a, b;

    Line();
    explicit Line(const Point &);
    Line(int x, int y);
    Line(const Point &, const Point &);
    Line(int ax, int ay, int bx, int by);
    virtual ~Line();

    void setA(int x, int y);
    void setB(int x, int y);

    void move_to(Point a, Point b);
    void move_to(int ax, int ay, int bx, int by);
    double length() const;

    bool is_point() const;
    bool operator==(const Line &);
    bool operator!=(const Line &);
};

#endif
