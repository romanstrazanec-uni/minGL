#ifndef LIBGRAPHICS_POINT_H
#define	LIBGRAPHICS_POINT_H

struct Point {
    int x, y;

    Point();
    Point(int x, int y);
    Point(const Point&);
    Point(Point &&) noexcept;
    virtual ~Point();

    Point& operator=(const Point &);
    Point& operator=(Point &&) noexcept;
    bool operator==(const Point &) const;
    bool operator!=(const Point &) const;

    void move_to(int x, int y);
    void move_to(const Point &);

    Point& operator+=(const Point &);
    friend Point operator+(Point, const Point &);
    Point& operator-=(const Point &);
    friend Point operator-(Point, const Point &);
};

#endif

