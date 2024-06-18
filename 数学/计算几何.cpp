#include <bits/stdc++.h>
using namespace std;
typedef double design_float;
const design_float PI = acos(-1);
const design_float EPS = 1e-9;
class Vector
{
    friend class Point;
    friend class Line;
    friend vector<Point> getHull(vector<Point> &points);

private:
    design_float x, y;

public:
    Vector(design_float x, design_float y) : x(x), y(y) {}
    Vector(design_float angle) : x(cos(angle)), y(sin(angle)) {}
    Vector(Point a, Point b) : x(b.x - a.x), y(b.y - a.y) {}
    Vector(Point a) : x(a.x), y(a.y) {}
    Vector operator+(Vector b)
    {
        return Vector{x + b.x, y + b.y};
    }
    Vector operator-(Vector b)
    {
        return Vector{x - b.x, y - b.y};
    }
    Vector operator*(design_float k)
    {
        return Vector{x * k, y * k};
    }
    Vector operator/(design_float k)
    {
        return Vector{x / k, y / k};
    }
    Vector operator*(Vector b)
    {
        return Vector{x * b.x, y * b.y};
    }
    design_float operator^(const Vector &b)
    {
        return x * b.y - y * b.x;
    }
};
class Point
{
    friend class Vector;
    friend class Line;
    friend vector<Point> getHull(vector<Point> &points);

private:
    design_float x, y;

public:
    Point(design_float x, design_float y) : x(x), y(y) {}
    Point operator+(Vector b)
    {
        return Point{x + b.x, y + b.y};
    }
    Vector operator-(Point b)
    {
        return Vector{x - b.x, y - b.y};
    }
    Point operator*(design_float k)
    {
        return Point{x * k, y * k};
    }
    Point operator/(design_float k)
    {
        return Point{x / k, y / k};
    }
    design_float operator^(Point b)
    {
        return x * b.y - y * b.x;
    }
    void rotate(design_float angle)
    {
        design_float x1 = x * cos(angle) - y * sin(angle);
        design_float y1 = x * sin(angle) + y * cos(angle);
        x = x1;
        y = y1;
    }
};
class Line
{
private:
    design_float st_x, st_y, ed_x, ed_y;

public:
    Line(design_float st_x, design_float st_y, design_float ed_x, design_float ed_y) : st_x(st_x), st_y(st_y), ed_x(ed_x), ed_y(ed_y) {}
    Line(Point a, Point b) : st_x(a.x), st_y(a.y), ed_x(b.x), ed_y(b.y) {}
    Line(Point a, Vector b) : st_x(a.x), st_y(a.y), ed_x(a.x + b.x), ed_y(a.y + b.y) {}
    design_float length()
    {
        return sqrt((st_x - ed_x) * (st_x - ed_x) + (st_y - ed_y) * (st_y - ed_y));
    }
    design_float angle()
    {
        return atan2(ed_y - st_y, ed_x - st_x);
    }
};


int main()
{
}