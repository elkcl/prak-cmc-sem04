#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

using ld = long double;

constexpr int PRECISION = 10;

class Point
{
  private:
    int64_t x, y;

  public:
    Point(int64_t _x = 0, int64_t _y = 0) : x{_x}, y{_y} {}
    int64_t
    get_x() const
    {
        return x;
    }
    int64_t
    get_y() const
    {
        return y;
    }

    friend Point operator+(const Point &a, const Point &b);
    friend Point operator-(const Point &a);
    friend Point operator-(const Point &a, const Point &b);
    friend Point operator*(const Point &a, int64_t k);
    friend Point operator*(int64_t k, const Point &a);
    friend int64_t operator*(const Point &a, const Point &b);
    friend int64_t operator%(const Point &a, const Point &b);
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
operator*(const Point &a, int64_t k)
{
    return {a.x * k, a.y * k};
}

Point
operator*(int64_t k, const Point &a)
{
    return {a.x * k, a.y * k};
}

int64_t
operator*(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}

int64_t
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
    Line(Point p1, Point p2) : p0{p1}, n{p2 - p1} {}
    bool
    contains(const Point &p) const
    {
        return (p - p0) % n == 0;
    }
    struct Intersection
    {
        enum
        {
            NONE = 0,
            POINT = 1,
            ALL = 2,
        } type;
        ld x, y;
    };
    friend bool operator==(const Line &l1, const Line &l2);
    friend bool operator||(const Line &l1, const Line &l2);
    friend Intersection operator%(const Line &l1, const Line &l2);
};

bool
operator||(const Line &l1, const Line &l2)
{
    return l1.n % l2.n == 0;
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
    ld t = static_cast<ld>((l2.p0 - l1.p0) % l2.n) / (l1.n % l2.n);
    return {Line::Intersection::POINT, l1.p0.get_x() + t * l1.n.get_x(), l1.p0.get_y() + t * l1.n.get_y()};
}

int
main()
{
    cout << std::fixed << std::setprecision(PRECISION);
    Point p1, p2, p3, p4;
    cin >> p1 >> p2 >> p3 >> p4;
    Line l1{p1, p2};
    Line l2{p3, p4};
    auto ans = l1 % l2;
    if (ans.type == Line::Intersection::POINT) {
        cout << ans.type << ' ' << ans.x << ' ' << ans.y << endl;
    } else {
        cout << ans.type << endl;
    }
}
