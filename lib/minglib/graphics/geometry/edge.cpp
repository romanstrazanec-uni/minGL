#include "edge.hpp"

Edge::Edge() = default;
Edge::Edge(const Point &end) : start(Point()), end(end) {}
Edge::Edge(const Edge &other) = default;
Edge::Edge(int x, int y) : start(Point()), end(Point(x, y)) {}
Edge::Edge(const Point &start, const Point &end) : start(start), end(end) {}
Edge::Edge(int startX, int startY, int endX, int endY) : start(Point(startX, startY)), end(Point(endX, endY)) {}
Edge::~Edge() = default;

void Edge::setStart(int x, int y) { start = Point(x, y); }
void Edge::setEnd(int x, int y) { end = Point(x, y); }

void Edge::move_to(const Point &startPoint, const Point &endPoint) {
    start = startPoint, end = endPoint;
}

void Edge::move_to(int startX, int startY, int endX, int endY) {
    start = Point(startX, startY), end = Point(endX, endY);
}

double Edge::deltaX() const {
    return fmax(start.x, end.x) - fmin(start.x, end.x);
}

double Edge::deltaY() const {
    return fmax(start.y, end.y) - fmin(start.y, end.y);
}

double Edge::length() const {
    if (start.x == end.x) return fabs((double) start.y - end.y);
    if (start.y == end.y) return fabs((double) start.x - end.x);
    return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
}

bool Edge::is_point() const { return start == end; }

Point Edge::middle() const {
    if (is_point()) return start;
    auto x = (int) deltaX() / 2;
    auto y = (int) deltaY() / 2;
    return Point(x, y);
}

Line Edge::line() {
    double m = deltaY() / deltaX();
    return Line(m, start.y / (m * start.x));
}

/* Comparision operators */
bool Edge::operator==(const Edge &l) { return start == l.start && end == l.end; }
bool Edge::operator!=(const Edge &l) { return !(*this == l); }
