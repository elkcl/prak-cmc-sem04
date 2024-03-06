#include <iomanip>
#include <new>
#include <string>
#include <sstream>
#include <cmath>
#include <new>
#include <utility>
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

class complex_stack
  {
  private:
    complex *buf;
    size_t cnt;
    static complex *
    stack_alloc(size_t count)
    {
      return static_cast<complex *>(::operator new(count * sizeof(complex), std::align_val_t{alignof(complex)}));
    }
    static void
    stack_free(complex *mem)
    {
      ::operator delete(mem, std::align_val_t{alignof(complex)});
    }

  public:
    complex_stack() : buf{nullptr}, cnt{0} {}
    ~complex_stack() noexcept
    {
      if (buf == nullptr) {
        return;
      }
      for (size_t i = 0; i < cnt; ++i) {
        buf[i].~complex();
      }
      stack_free(buf);
    }
    complex_stack(const complex_stack &oth) : cnt{oth.cnt}, buf{stack_alloc(oth.cnt)}
    {
      for (size_t i = 0; i < cnt; ++i) {
        new (buf + i) complex(oth.buf[i]);
      }
    }
    complex_stack(complex_stack &&oth) noexcept : cnt{std::exchange(oth.cnt, 0)}, buf{std::exchange(oth.buf, nullptr)}
    {
    }
    complex_stack &
    operator=(complex_stack oth)
    {
      std::swap(cnt, oth.cnt);
      std::swap(buf, oth.buf);
      return *this;
    }
    complex_stack &
    operator=(complex_stack &&oth) noexcept
    {
      cnt = std::exchange(oth.cnt, 0);
      buf = std::exchange(oth.buf, nullptr);
      return *this;
    }
  };
} // namespace numbers
