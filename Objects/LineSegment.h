#ifndef LIBGRAPHICS_LINE_H
#define LIBGRAPHICS_LINE_H

#include <cmath>
#include "Point.h"

struct LineSegment {
    Point start{Point()}, end{Point()};

    // constructors
    LineSegment(); // start and end set to {0,0}
    explicit LineSegment(const Point &end); // start set to {0,0}
    LineSegment(const LineSegment &); // copy constructor
    LineSegment(LineSegment &&) noexcept; // move construcctor
    LineSegment(int x, int y); // start set to {0,0}
    LineSegment(const Point &, const Point &);
    LineSegment(int startx, int starty, int endx, int endy);
    virtual ~LineSegment(); // destructor

    void setStart(int x, int y);
    void setEnd(int x, int y);

    void move_to(const Point &start, const Point &end);
    void move_to(int startx, int starty, int endx, int endy);

    double length() const;
    bool is_point() const;
    Point center() const;

    // comparision operators
    bool operator==(const LineSegment &);
    bool operator!=(const LineSegment &);
};

#endif
