#include "Line.h"

Line::Line(): a(Point()), b(Point()){}
Line::Line(const Point &p): a(Point()), b(p){}
Line::Line(int x, int y): a(Point()), b(Point(x, y)){}
Line::Line(const Point &a, const Point &b): a(a), b(b){}
Line::Line(int ax, int ay, int bx, int by): a(Point(ax, ay)), b(Point(bx, by)){}
Line::~Line() = default;

void Line::setA(int x, int y) { a = Point(x, y); }
void Line::setB(int x, int y) { b = Point(x, y); }

void Line::move_to(Point a, Point b){ this->a = a; this->b = b; }
void Line::move_to(int ax, int ay, int bx, int by){ this->a = Point(ax, ay); this->b = Point(bx, by); }
double Line::length() const {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

bool Line::is_point() const { return a == b; }
bool Line::operator==(const Line &l){ return a == l.a && b == l.b; }
bool Line::operator!=(const Line &l){ return !(*this == l); }