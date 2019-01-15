#include "Circle.h"

Circle::Circle(): c(), r(0){}
Circle::Circle(unsigned int r): c(), r(r) {}
Circle::Circle(const Point &c, unsigned int r): c(c), r(r) {}
Circle::Circle(int x, int y, unsigned int r): c(Point(x, y)), r(r) {}

bool Circle::is_point() { return r == 0; }

Circle::~Circle() = default;
