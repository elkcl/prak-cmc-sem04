#include <iomanip>
#include <iostream>
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

template <typename T> class immut_stack;

// copy-on-write shared memory pool for the stack
template <typename T> class mem_pool
{
private:
    T *buf;
    size_t *refcount;
    size_t cap;
    size_t *maxpos;

public:
    explicit mem_pool(size_t count) : cap{count}
    {
        refcount = new size_t{1};
        maxpos = new size_t{0};
        buf = static_cast<T *>(::operator new(count * sizeof(T), std::align_val_t{alignof(T)}));
    }
    ~mem_pool()
    {
        if (buf == nullptr) {
            return;
        }
        --(*refcount);
        if (*refcount == 0) {
            for (size_t i = 0; i < *maxpos; ++i) {
                buf[i].~T();
            }
            delete refcount;
            delete maxpos;
            ::operator delete(buf, std::align_val_t{alignof(T)});
        }
    }
    mem_pool(const mem_pool &oth) : buf{oth.buf}, refcount{oth.refcount}, cap{oth.cap}, maxpos{oth.maxpos}
    {
        ++(*refcount);
    }
    mem_pool(mem_pool &&oth) noexcept
        : buf{std::exchange(oth.buf, nullptr)}, refcount{std::exchange(oth.refcount, nullptr)},
          cap{std::exchange(oth.cap, 0)}, maxpos{std::exchange(oth.maxpos, nullptr)}
    {
    }
    mem_pool &
    operator=(mem_pool oth) noexcept
    {
        std::swap(buf, oth.buf);
        std::swap(refcount, oth.refcount);
        std::swap(cap, oth.cap);
        std::swap(maxpos, oth.maxpos);
        return *this;
    }
    mem_pool
    realloc(size_t count)
    {
        mem_pool res{count};
        for (size_t i = 0; i < std::min(*maxpos, count); ++i) {
            new (res.buf + i) T{buf[i]};
        }
        return res;
    }
    friend immut_stack<T>;
    friend immut_stack<T> operator<<(immut_stack<T> stack, complex elem);
};

template <typename T> class immut_stack
{
private:
    mem_pool<T> mem{1};
    size_t cnt{0};

public:
    size_t
    size() const
    {
        return cnt;
    }
    const T &
    operator[](size_t ix) const
    {
        return mem.buf[ix];
    }
    const T &
    operator+() const
    {
        return mem.buf[cnt - 1];
    }
    friend immut_stack
    operator~(immut_stack stack)
    {
        --stack.cnt;
        return stack;
    }
    friend immut_stack
    operator<<(immut_stack stack, complex elem)
    {
        if (stack.cnt != *stack.mem.maxpos || stack.cnt >= stack.mem.cap) {
            stack.mem = stack.mem.realloc(stack.cnt * 2 + 2);
        }
        new (stack.mem.buf + stack.cnt) complex{elem};
        ++stack.cnt;
        *stack.mem.maxpos = stack.cnt;
        return stack;
    }
};

using complex_stack = immut_stack<complex>;
} // namespace numbers

int
main()
{
    numbers::complex_stack st1;
    st1 = st1 << 2;
    numbers::complex_stack st21 = st1 << numbers::complex{"(1,2)"};
    numbers::complex_stack st22 = st1 << 3 << 4;
    numbers::complex_stack st221 = ~st22;
    std::cout << (+st221).to_string() << std::endl;
    for (size_t i = 0; i < st21.size(); ++i) {
        std::cout << st21[i].to_string() << ' ';
    }
    std::cout << std::endl;
    for (size_t i = 0; i < st22.size(); ++i) {
        std::cout << st22[i].to_string() << ' ';
    }
    std::cout << std::endl;
}
