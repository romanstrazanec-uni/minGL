#include "Line.h"

// constructors
Line::Line(): start(Point()), end(Point()){}
Line::Line(const Point &end): start(Point()), end(end){}
Line::Line(const Line &other) = default;
Line::Line(Line &&) noexcept = default;
Line::Line(int x, int y): start(Point()), end(Point(x, y)){}
Line::Line(const Point &start, const Point &end): start(start), end(end){}
Line::Line(int startx, int starty, int endx, int endy): start(Point(startx, starty)), end(Point(endx, endy)){}
Line::~Line() = default;

void Line::setStart(int x, int y) { start = Point(x, y); }
void Line::setEnd(int x, int y) { end = Point(x, y); }

void Line::move_to(const Point &start, const Point &end){
    this->start = start, this->end = end;
}
void Line::move_to(int startx, int starty, int endx, int endy){
    start = Point(startx, starty), end = Point(endx, endy);
}

double Line::length() const {
    if(start.x == end.x) return fabs((double)start.y - end.y);
    if(start.y == end.y) return fabs((double)start.x - end.x);
    return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
}
bool Line::is_point() const { return start == end; }
Point Line::center() const {
    if(is_point()) return start;
    auto x = (int)round((fmax(start.x, end.x) - fmin(start.x, end.x)) / 2);
    auto y = (int)round((fmax(start.y, end.y) - fmin(start.y, end.y)) / 2);
    return Point(x, y);
}

bool Line::operator==(const Line &l){ return start == l.start && end == l.end; }
bool Line::operator!=(const Line &l){ return !(*this == l); }




