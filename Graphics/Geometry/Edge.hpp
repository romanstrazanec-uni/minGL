#ifndef MINGL_EDGE_HPP_INCLUDED
#define MINGL_EDGE_HPP_INCLUDED

#include <cmath>
#include "geometry.hpp"

struct Edge {
    Point start{Point()}, end{Point()};

    Edge();
    explicit Edge(const Point &end);
    Edge(const Edge &);
    Edge(int x, int y);
    Edge(const Point &, const Point &);
    Edge(int startx, int starty, int endx, int endy);
    virtual ~Edge();

    void setStart(int x, int y);
    void setEnd(int x, int y);

    void move_to(const Point &start, const Point &end);
    void move_to(int startx, int starty, int endx, int endy);

    double deltax() const;
    double deltay() const;
    double length() const;
    bool is_point() const;
    Point middle() const;
    Line line();

    // comparision operators
    bool operator==(const Edge &);
    bool operator!=(const Edge &);
};

#endif
