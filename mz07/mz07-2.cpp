#include <cmath>
#include <sstream>
#include <string>
#include <cstdio>

class Rectangle : public Figure
{
private:
    double a, b;

public:
    Rectangle(double _a, double _b)
    {
        a = _a;
        b = _b;
    }
    static Rectangle *
    make(std::string st)
    {
        std::istringstream ss(st);
        double a, b;
        ss >> a >> b;
        return new Rectangle(a, b);
    }
    virtual double
    get_square() const
    {
        return a * b;
    }
};
class Square : public Figure
{
private:
    double a;

public:
    Square(double _a) { a = _a; }
    static Square *
    make(std::string st)
    {
        std::istringstream ss(st);
        double a;
        ss >> a;
        return new Square(a);
    }
    virtual double
    get_square() const
    {
        return a * a;
    }
};
class Circle : public Figure
{
private:
    double r;

public:
    Circle(double _r) { r = _r; }
    static Circle *
    make(std::string st)
    {
        std::istringstream ss(st);
        double r;
        ss >> r;
        return new Circle(r);
    }
    virtual double
    get_square() const
    {
        return std::acos(-1) * r * r;
    }
};
