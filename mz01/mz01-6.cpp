#include <cmath>
#include <iostream>

using ld = long double;

class Point {
private:
    const ld x, y, absv;
public:
    Point(ld _x, ld _y) : x{_x}, y{_y}, absv{sqrt(x * x + y * y)} {}
    ld abs() const {
        return absv;
    }

    Point norm() const {
        return *this / absv;
    }

    friend Point operator+(const Point &a, const Point &b);
    friend Point operator-(const Point &a);
    friend Point operator-(const Point &a, const Point &b);
    friend Point operator*(const Point &a, ld k);
    friend Point operator*(ld k, const Point &a);
    friend Point operator/(const Point &a, ld k);
    friend ld operator*(const Point &a, const Point &b);
    friend ld operator%(const Point &a, const Point &b);
};

Point operator+(const Point &a, const Point &b) {
    return {a.x + b.x, a.y + b.y};
}
Point operator-(const Point &a) {
    return {-a.x, -a.y};
}
Point operator-(const Point &a, const Point &b) {
    return {a.x - b.x, a.y - b.y};
}
Point operator*(const Point &a, ld k) {
    return {a.x * k, a.y * k};
}
Point operator*(ld k, const Point &a) {
    return {a.x * k, a.y * k};
}
Point operator/(const Point &a, ld k) {
    return {a.x / k, a.y / k};
}
ld operator*(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
ld operator%(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

class Line {
private:
    const Point p0, n;
public:
    Line(Point p1, Point p2) : p0{p1}, n{(p1 - p0).norm()} {}
    friend bool operator==(const Line &l1, const Line &l2);
    friend bool operator||(const Line &l1, const Line &l2);
    friend Point operator%(const Line &l1, const Line &l2);
}

int main() {

}
