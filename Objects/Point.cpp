#include "Point.h"

Point::Point(): x(0), y(0) {}
Point::Point(int x, int y): x(x), y(y) {}
Point::Point(const Point& other) { *this = other; }
Point::Point(Point &&other) noexcept { *this = other; }
Point::~Point() = default;

void Point::move_to(int x, int y) {
  this->x = x;
  this->y = y;
}
void Point::move_to(const Point& point){
  x = point.x;
  y = point.y;
}

Point& Point::operator=(const Point& other) = default;
bool Point::operator==(const Point &other) const {
  return x == other.x && y == other.y;
}
bool Point::operator!=(const Point &other) const { return !(*this == other); }

Point& Point::operator+=(const Point& other){
    this->x += x;
    this->y += y;
    return *this;
}
Point operator+(Point p1, const Point& p2){ return p1 += p2; }

Point& Point::operator-=(const Point& other){
  this->x -= x;
  this->y -= y;
  return *this;
}
Point operator-(Point p1, const Point& p2){ return p1 -= p2; }

std::ostream& operator<<(std::ostream& out, const Point& point) {
  out << "Point(" << point.x << "," << point.y << ")";
  return out;
}
