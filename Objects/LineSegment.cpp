#include "LineSegment.h"

// constructors
LineSegment::LineSegment() = default;
LineSegment::LineSegment(const Point &end): start(Point()), end(end){}
LineSegment::LineSegment(const LineSegment &other) = default;
LineSegment::LineSegment(LineSegment &&) noexcept = default;
LineSegment::LineSegment(int x, int y): start(Point()), end(Point(x, y)){}
LineSegment::LineSegment(const Point &start, const Point &end): start(start), end(end){}
LineSegment::LineSegment(int startx, int starty, int endx, int endy): start(Point(startx, starty)), end(Point(endx, endy)){}
LineSegment::~LineSegment() = default;

void LineSegment::setStart(int x, int y) { start = Point(x, y); }
void LineSegment::setEnd(int x, int y) { end = Point(x, y); }

void LineSegment::move_to(const Point &start, const Point &end){
    this->start = start, this->end = end;
}
void LineSegment::move_to(int startx, int starty, int endx, int endy){
    start = Point(startx, starty), end = Point(endx, endy);
}

double LineSegment::deltax() const {
    return fmax(start.x, end.x) - fmin(start.x, end.x);
}
double LineSegment::deltay() const {
    return fmax(start.y, end.y) - fmin(start.y, end.y);
}
double LineSegment::length() const {
    if(start.x == end.x) return fabs((double)start.y - end.y);
    if(start.y == end.y) return fabs((double)start.x - end.x);
    return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
}
bool LineSegment::is_point() const { return start == end; }
Point LineSegment::center() const {
    if(is_point()) return start;
    auto x = (int)deltax() / 2;
    auto y = (int)deltay() / 2;
    return Point(x, y);
}
Line LineSegment::line() const {
    double m = deltay()/deltax();
    return Line(m, start.y/(m*start.x));
}

bool LineSegment::operator==(const LineSegment &l){ return start == l.start && end == l.end; }
bool LineSegment::operator!=(const LineSegment &l){ return !(*this == l); }


