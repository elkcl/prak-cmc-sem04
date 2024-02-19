#include <cstdint>

class Sum
{
  private:
    const int64_t a, b, c;

  public:
    Sum(int64_t _a = 0, int64_t _b = 0) : a{_a}, b{_b}, c{_a + _b} {}
    Sum(const Sum &_s, int64_t _c) : a{_s.c}, b{_c}, c{_s.c + _c} {}
    int64_t
    get() const
    {
        return c;
    }
};
