#include "point.hpp"

Point::Point() = default;
Point::Point(int x, int y) : x(x), y(y) {}
Point::Point(const Point &other) = default;
Point::~Point() = default;

void Point::move_to(int newX, int newY) { x = newX, y = newY; }
void Point::move_to(const Point &point) { *this = point; }

/* Assignment operators */
Point &Point::operator=(const Point &other) {
    x = other.x, y = other.y;
    return *this;
}

Point &Point::operator+=(const Point &other) {
    x += other.x, y += other.y;
    return *this;
}

Point &Point::operator-=(const Point &other) {
    x -= other.x, y -= other.y;
    return *this;
}

Point &Point::operator*=(int f) {
    x *= f, y *= f;
    return *this;
}

Point &Point::operator/=(int f) {
    x /= f, y /= f;
    return *this;
}

/* Comparision operators */
bool Point::operator==(const Point &other) const { return x == other.x && y == other.y; }
bool Point::operator!=(const Point &other) const { return !(*this == other); }

/* Arithmetic operators */
Point operator+(Point p1, const Point &p2) { return p1 += p2; }
Point operator-(Point p1, const Point &p2) { return p1 -= p2; }
Point operator*(Point point, int f) { return point *= f; }
Point operator*(int f, Point point) { return point *= f; }
Point operator/(Point point, int f) { return point /= f; }
Point operator/(int f, Point point) { return point /= f; }
