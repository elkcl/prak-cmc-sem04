#include <cmath>
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

using ld = long double;

constexpr ld EPS = 1e-9;
constexpr int PRECISION = 6;

class Point
{
  private:
    ld x, y, absval;

  public:
    Point(ld _x = 0.0, ld _y = 0.0) : x{_x}, y{_y}, absval{sqrt(x * x + y * y)} {}
    ld
    absv() const
    {
        return absval;
    }

    Point
    norm() const
    {
        return *this / absval;
    }

    friend Point operator+(const Point &a, const Point &b);
    friend Point operator-(const Point &a);
    friend Point operator-(const Point &a, const Point &b);
    friend Point operator*(const Point &a, ld k);
    friend Point operator*(ld k, const Point &a);
    friend Point operator/(const Point &a, ld k);
    friend ld operator*(const Point &a, const Point &b);
    friend ld operator%(const Point &a, const Point &b);
    friend std::istream &operator>>(std::istream &in, Point &p);
    friend std::ostream &operator<<(std::ostream &out, const Point &p);
};

Point
operator+(const Point &a, const Point &b)
{
    return {a.x + b.x, a.y + b.y};
}
Point
operator-(const Point &a)
{
    return {-a.x, -a.y};
}
Point
operator-(const Point &a, const Point &b)
{
    return {a.x - b.x, a.y - b.y};
}
Point
operator*(const Point &a, ld k)
{
    return {a.x * k, a.y * k};
}
Point
operator*(ld k, const Point &a)
{
    return {a.x * k, a.y * k};
}
Point
operator/(const Point &a, ld k)
{
    return {a.x / k, a.y / k};
}
ld
operator*(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}
ld
operator%(const Point &a, const Point &b)
{
    return a.x * b.y - a.y * b.x;
}

std::istream &
operator>>(std::istream &in, Point &p)
{
    in >> p.x >> p.y;
    return in;
}

std::ostream &
operator<<(std::ostream &out, const Point &p)
{
    out << p.x << ' ' << p.y;
    return out;
}

class Line
{
  private:
    const Point p0, n;

  public:
    Line(Point p1, Point p2) : p0{p1}, n{(p2 - p1).norm()} {}
    bool
    contains(const Point &p) const
    {
        return abs((p - p0) % n) < EPS;
    }
    struct Intersection
    {
        enum
        {
            NONE = 0,
            POINT = 1,
            ALL = 2,
        } type;
        Point p;
    };
    friend bool operator==(const Line &l1, const Line &l2);
    friend bool operator||(const Line &l1, const Line &l2);
    friend Intersection operator%(const Line &l1, const Line &l2);
};

bool
operator||(const Line &l1, const Line &l2)
{
    return abs(l1.n % l2.n) < EPS;
}

bool
operator==(const Line &l1, const Line &l2)
{
    return l1.contains(l2.p0) && (l1 || l2);
}

Line::Intersection
operator%(const Line &l1, const Line &l2)
{
    if (l1 == l2) {
        return {Line::Intersection::ALL};
    }
    if (l1 || l2) {
        return {Line::Intersection::NONE};
    }
    ld t = (l2.p0 - l1.p0) % l2.n / (l1.n % l2.n);
    return {Line::Intersection::POINT, l1.p0 + t * l1.n};
}

int
main()
{
    cout << std::setprecision(PRECISION);
    Point p1, p2, p3, p4;
    cin >> p1 >> p2 >> p3 >> p4;
    Line l1{p1, p2};
    Line l2{p3, p4};
    auto ans = l1 % l2;
    cout << ans.type << endl;
    if (ans.type == Line::Intersection::POINT) {
        cout << ans.p << endl;
    }
}
