#include <bits/stdc++.h>
typedef double design_float;
const design_float PI = acos(-1);
const design_float eps = 1e-7;
struct Vector
{
    design_float x, y;
    Vector(design_float x = 0, design_float y = 0)
        : x(x), y(y)
    {
    }
    bool operator==(const Vector &b) const { return fabs(x - b.x) <= eps && fabs(y - b.y) <= eps; }
    Vector operator+(const Vector &b) const { return Vector(x + b.x, y + b.y); }
    Vector operator-(const Vector &b) const { return Vector(x - b.x, y - b.y); }
    Vector operator*(const design_float &b) const { return Vector(x * b, y * b); }
    Vector operator/(const design_float &b) const { return Vector(x / b, y / b); }
    design_float operator*(const Vector &b) const { return x * b.x + y * b.y; }
    // 重定义^为叉乘
    design_float operator^(const Vector &b) const { return x * b.y - y * b.x; }
    design_float length() const { return sqrt(x * x + y * y); }
    design_float angle() const { return atan2(y, x); }
    Vector unit() const { return *this / length(); }
    // 将向量旋转angle角度，angle为弧度制
    Vector rotate(design_float angle) const
    {
        return Vector(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
    }
};
typedef Vector Point;
struct Line
{
    Point a, b;
    Vector vec() { return b - a; }
    Line(Point a = Point(), Point b = Point())
        : a(a), b(b)
    {
    }
    // 判断点c在直线上
    bool isPointOnLine(Point c) { return ((b - a) ^ (c - a)) == 0; }
    // 判断点c在线段上
    bool isPointOnSegment(Point c)
    {
        return fabs((b - a) ^ (c - a)) <= eps && (c - a) * (c - b) <= eps;
    }
    // 求点c到直线的距离
    design_float distanceToLine(Point c)
    {
        return fabs(((b - a) ^ (c - a)) / (b - a).length());
    }
    // 求点c到线段的距离
    design_float distanceToSegment(Point c)
    {
        if ((c - a) * (b - a) < 0)
            return (c - a).length();
        if ((c - b) * (a - b) < 0)
            return (c - b).length();
        return distanceToLine(c);
    }
    // 求点c到线段的最近点
    Point nearestPointToSegment(Point c)
    {
        if ((c - a) * (b - a) < 0)
            return a;
        if ((c - b) * (a - b) < 0)
            return b;
        design_float r = (c - a) * (b - a) / (b - a).length();
        return a + (b - a).unit() * r;
    }
};
namespace Geometry
{
    Point rotate(Point p, Point base, design_float angle)
    {
        return (p - base).rotate(angle) + base;
    }
    Point intersection(Line l1, Line l2)
    {
        design_float s1 = (l2.b - l2.a) ^ (l1.a - l2.a);
        design_float s2 = (l2.b - l2.a) ^ (l1.b - l2.a);
        return (l1.a * s2 - l1.b * s1) / (s2 - s1);
    }
    // 输入一个点集，返回凸包
    std::vector<Point> getHull(std::vector<Point> p)
    {
        std::vector<Point> h, l;
        std::sort(p.begin(), p.end(), [&](auto a, auto b)
                  {
        if (a.x != b.x) {
            return a.x < b.x;
        } else {
            return a.y < b.y;
        } });
        p.erase(std::unique(p.begin(), p.end()), p.end());
        if (p.size() <= 1)
        {
            return p;
        }

        for (auto a : p)
        {
            while (h.size() > 1 && ((a - h.back()) ^ (a - h[h.size() - 2])) <= 0)
                h.pop_back();
            while (l.size() > 1 && ((a - l.back()) ^ (a - l[l.size() - 2])) >= 0)
                l.pop_back();
            l.push_back(a);
            h.push_back(a);
        }
        l.pop_back();
        std::reverse(h.begin(), h.end());
        h.pop_back();
        l.insert(l.end(), h.begin(), h.end());
        return l;
    }
    // 计算凸包的边长
    design_float getHullLength(std::vector<Point> hull)
    {
        design_float res = 0;
        for (int i = 0; i < hull.size(); i++)
            res += (hull[i] - hull[(i + 1) % hull.size()]).length();
        return res;
    }
    // 计算凸包的面积
    design_float getHullArea(std::vector<Point> hull)
    {
        design_float res = 0;
        for (int i = 0; i < hull.size(); i++)
            res += (hull[i] ^ hull[(i + 1) % hull.size()]);
        return fabs(res) / 2;
    }
    bool pointOnLeft(Point p, Line l)
    {
        return ((l.b - l.a) ^ (p - l.a)) > eps;
    }
    // 求半平面交，给定若干条有向线段，算法将其排序后，以左边为半平面，返回交的凸包。
    std::vector<Point> getHalfPlane(std::vector<Line> lines)
    {
        sort(lines.begin(), lines.end(), [](auto a, auto b)
             {
            design_float angle1 = a.vec().angle(), angle2 = b.vec().angle();
            if (fabs(angle1 - angle2) <= eps)
                return pointOnLeft(a.a, b);
            else
                return angle1 < angle2; });
        std::vector<Line> res;
        for (auto x : lines)
        {
            if (!res.empty() && fabs(x.vec().angle() - res.back().vec().angle()) <= eps)
                continue;
            res.push_back(x);
        }
        lines.swap(res);
        int len = lines.size();
        int l = 1, r = 0;
        std::vector<int> q(len * 2);
        std::vector<Point> p(len * 2);
        for (int i = 0; i < len; i++)
        {
            while (l < r && !pointOnLeft(p[r], lines[i]))
                r--;
            while (l < r && !pointOnLeft(p[l + 1], lines[i]))
                l++;
            q[++r] = i;
            if (l < r && fabs((lines[q[r]].vec() ^ lines[q[r - 1]].vec())) <= eps)
                if (lines[q[r]].vec() * lines[q[r - 1]].vec() < -eps)
                    return std::vector<Point>();
            if (l < r)
                p[r] = intersection(lines[q[r]], lines[q[r - 1]]);
        }
        while (l < r && !pointOnLeft(p[r], lines[q[l]]))
            r--;
        if (r - l <= 1)
            return std::vector<Point>();
        p[l] = intersection(lines[q[r]], lines[q[l]]);
        std::vector<Point> ans;
        while (l <= r)
        {
            ans.push_back(p[l]);
            l++;
        }
        return ans;
    }
}