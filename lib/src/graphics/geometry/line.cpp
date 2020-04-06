#include "line.hpp"

Line::Line() = default;
Line::Line(double slope) : m(slope), b(0) {}
Line::Line(double slope, double b) : m(slope), b(b) {}
Line::Line(const Line &) = default;
Line::~Line() = default;

double Line::y(double x) { return m * x + b; }

Point Line::point(int x) { return Point(x, (int) round(y(x))); }

Edge Line::segment(int startX, int endX) {
    return Edge(point(startX), point(endX));
}
