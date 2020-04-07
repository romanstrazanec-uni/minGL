#include "circle.hpp"

Circle::Circle() = default;
Circle::Circle(unsigned int r) : r(r) {}
Circle::Circle(const Point &c, unsigned int r) : c(c), r(r) {}
Circle::Circle(int x, int y, unsigned int r) : c(Point(x, y)), r(r) {}
Circle::~Circle() = default;

bool Circle::is_point() { return r == 0; }
void Circle::move_to(const Point &point) { c = point; }
void Circle::move_to(int x, int y) { c = Point(x, y); }

bool Circle::operator==(const Circle &other) const { return c == other.c && r == other.r; }
bool Circle::operator!=(const Circle &other) const { return !(*this == other); }
