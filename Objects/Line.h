#ifndef LIBGRAPHICS_LINE_H
#define LIBGRAPHICS_LINE_H

#include <cmath>
#include "Point.h"

struct Line {
    Point start, end;

    // constructors
    Line(); // start and end set to {0,0}
    explicit Line(const Point &end); // start set to {0,0}
    Line(const Line &); // copy constructor
    Line(Line &&) noexcept; // move construcctor
    Line(int x, int y); // start set to {0,0}
    Line(const Point &, const Point &);
    Line(int startx, int starty, int endx, int endy);
    virtual ~Line(); // destructor

    void setStart(int x, int y);
    void setEnd(int x, int y);

    void move_to(const Point &start, const Point &end);
    void move_to(int startx, int starty, int endx, int endy);

    double length() const;
    bool is_point() const;
    Point center() const;

    // comparision operators
    bool operator==(const Line &);
    bool operator!=(const Line &);
};

#endif
