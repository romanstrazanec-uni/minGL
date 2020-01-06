#ifndef MINGL_EDGE_INCLUDED
#define MINGL_EDGE_INCLUDED

#include "geometry.hpp"

struct Edge {
    Point start{Point()}, end{Point()};

    Edge();
    explicit Edge(const Point &end);
    Edge(const Edge &);
    Edge(int x, int y);
    Edge(const Point &, const Point &);
    Edge(int startX, int startY, int endX, int endY);

    virtual ~Edge();

    void setStart(int x, int y);
    void setEnd(int x, int y);

    void move_to(const Point &start, const Point &end);
    void move_to(int startX, int startY, int endX, int endY);

    double deltaX() const;
    double deltaY() const;

    double length() const;

    bool is_point() const;

    Point middle() const;

    Line line();

    /* Comparision operators */
    bool operator==(const Edge &);
    bool operator!=(const Edge &);
};

#endif
