#ifndef LIBGRAPHICS_LINESEGMENT_H
#define LIBGRAPHICS_LINESEGMENT_H

#include <cmath>
#include "Point.h"
#include "Line.h"

struct LineSegment {
    Point start{Point()}, end{Point()};

    LineSegment();
    explicit LineSegment(const Point &end);
    LineSegment(const LineSegment &);
    LineSegment(int x, int y);
    LineSegment(const Point &, const Point &);
    LineSegment(int startx, int starty, int endx, int endy);
    virtual ~LineSegment();

    void setStart(int x, int y);
    void setEnd(int x, int y);

    void move_to(const Point &start, const Point &end);
    void move_to(int startx, int starty, int endx, int endy);

    double deltax() const;
    double deltay() const;
    double length() const;
    bool is_point() const;
    Point middle() const;
    Line line() const;

    // comparision operators
    bool operator==(const LineSegment &);
    bool operator!=(const LineSegment &);
};

#endif
