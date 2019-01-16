#ifndef LIBGRAPHICS_POINT_H
#define	LIBGRAPHICS_POINT_H

struct Point {
    int x{0}, y{0};

    Point();
    Point(int x, int y);
    Point(const Point&);
    virtual ~Point();

    void move_to(int x, int y);
    void move_to(const Point &);

    // assignment operators
    Point& operator=(const Point &);
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
    friend Point operator*(Point, int);
    friend Point operator*(int, Point);
    friend Point operator/(Point, int);
    friend Point operator/(int, Point);
};

#endif

