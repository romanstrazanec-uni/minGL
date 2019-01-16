#ifndef LIBGRAPHICS_POINT_H
#define	LIBGRAPHICS_POINT_H

struct Point {
    int x, y;

    // constructors
    Point(); // {x,y} = {0,0}
    Point(int x, int y);
    Point(const Point&); // copy constructor
    Point(Point &&) noexcept; // move constructor
    virtual ~Point(); // destructor

    void move_to(int x, int y);
    void move_to(const Point &);

    // assignment operators
    Point& operator=(const Point &); // copy assignment
    Point& operator=(Point &&) noexcept; // move assignment
    Point& operator+=(const Point &);
    Point& operator-=(const Point &);
    Point& operator*=(int);
    Point& operator/=(int);

    // comparision operators
    bool operator==(const Point &) const;
    bool operator!=(const Point &) const;

    // arithmetic operators
    friend Point operator+(Point, const Point &);
    friend Point operator-(Point, const Point &);
    friend Point& operator*(const Point &, int);
    friend Point& operator*(int, const Point &);
    friend Point& operator/(const Point &, int);
    friend Point& operator/(int, const Point &);
};

#endif

