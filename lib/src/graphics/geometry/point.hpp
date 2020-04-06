#ifndef MINGL_POINT_INCLUDED
#define MINGL_POINT_INCLUDED

struct Point {
    int x{0}, y{0};

    Point();
    Point(int x, int y);
    Point(const Point &);
    virtual ~Point();

    void move_to(int x, int y);
    void move_to(const Point &);

    /* Assignment operators */
    Point &operator=(const Point &);
    Point &operator+=(const Point &);
    Point &operator-=(const Point &);
    Point &operator*=(int);
    Point &operator/=(int);

    /* Comparision operators */
    bool operator==(const Point &) const;
    bool operator!=(const Point &) const;

    /* Arithmetic operators */
    friend Point operator+(Point, const Point &);
    friend Point operator-(Point, const Point &);
    friend Point operator*(Point, int);
    friend Point operator*(int, Point);
    friend Point operator/(Point, int);
    friend Point operator/(int, Point);
};

#endif

