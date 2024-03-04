#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
namespace numbers
{
class complex
{
  private:
    double x, y;
    static constexpr int OUT_PRECISION{10};

  public:
    complex(double _re = 0, double _im = 0) : x{_re}, y{_im} {}
    explicit complex(const std::string &s)
    {
        std::istringstream iss{s};
        char ign;
        iss >> ign >> x >> ign >> y >> ign;
    }
    double
    re() const
    {
        return x;
    }
    double
    im() const
    {
        return y;
    }
    double
    abs2() const
    {
        return x * x + y * y;
    }
    double
    abs() const
    {
        return sqrt(abs2());
    }
    std::string
    to_string() const
    {
        std::ostringstream oss;
        oss << std::setprecision(OUT_PRECISION) << '(' << x << ',' << y << ')';
        return oss.str();
    }
    complex
    operator~() const
    {
        return {x, -y};
    }
    complex
    operator-() const
    {
        return {-x, -y};
    }
    complex &
    operator+=(const complex &b)
    {
        x += b.x;
        y += b.y;
        return *this;
    }
    complex &
    operator-=(const complex &b)
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }
    complex &
    operator*=(const complex &b)
    {
        complex res{x * b.x - y * b.y, x * b.y + y * b.x};
        return *this = res;
    }
    complex &
    operator/=(const complex &b)
    {
        double b_abs2 = b.abs2();
        complex b1{b.x / b_abs2, -b.y / b_abs2};
        return *this *= b1;
    }
};

complex
operator+(const complex &a, const complex &b)
{
    complex res{a};
    return res += b;
}
complex
operator-(const complex &a, const complex &b)
{
    complex res{a};
    return res -= b;
}
complex
operator*(const complex &a, const complex &b)
{
    complex res{a};
    return res *= b;
}
complex
operator/(const complex &a, const complex &b)
{
    complex res{a};
    return res /= b;
}
} // namespace numbers
