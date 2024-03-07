#include <iomanip>
#include <new>
#include <string>
#include <sstream>
#include <cmath>
#include <new>
#include <utility>
namespace numbers
{
template <typename T> class immut_stack;
// copy-on-write shared memory pool for the stack
template <typename T> class mem_pool
{
private:
    T *buf = nullptr;
    size_t *refcount = nullptr;
    size_t cap = 0;
    size_t *maxpos = nullptr;

public:
    explicit mem_pool(size_t count) : cap{count}
    {
        try {
            refcount = new size_t{1};
            maxpos = new size_t{0};
            buf = static_cast<T *>(::operator new(count * sizeof(T), std::align_val_t{alignof(T)}));
        } catch (...) {
            delete refcount;
            delete maxpos;
            ::operator delete(buf, std::align_val_t{alignof(T)});
            throw;
        }
    }
    ~mem_pool() noexcept(noexcept(~T()))
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
    mem_pool(const mem_pool &oth) noexcept : buf{oth.buf}, refcount{oth.refcount}, cap{oth.cap}, maxpos{oth.maxpos}
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
// ejudge has -Werror flag configured, which makes the run fail with CE due to the warning
// however, the warning in this case is not an error, I indeed need to deliberately make a non-template friend, which is
// further defined in the immut_stack class
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-template-friend"
    friend immut_stack<T> operator<<(immut_stack<T> stack, T elem);
#pragma GCC diagnostic pop
};

template <typename T> class immut_stack
{
private:
    mem_pool<T> mem{1};
    size_t cnt{0};

public:
    size_t
    size() const noexcept
    {
        return cnt;
    }
    const T &
    operator[](size_t ix) const noexcept
    {
        return mem.buf[ix];
    }
    const T &
    operator+() const noexcept
    {
        return mem.buf[cnt - 1];
    }
    friend immut_stack
    operator~(immut_stack stack) noexcept
    {
        --stack.cnt;
        return stack;
    }
    friend immut_stack
    operator<<(immut_stack stack, T elem)
    {
        // reallocate memory only if either the capacity is reached or the stack needs to be forked
        if (stack.cnt != *stack.mem.maxpos || stack.cnt >= stack.mem.cap) {
            stack.mem = stack.mem.realloc(stack.cnt * 2 + 2);
        }
        new (stack.mem.buf + stack.cnt) T{elem};
        ++stack.cnt;
        *stack.mem.maxpos = stack.cnt;
        return stack;
    }
};

using complex_stack = immut_stack<complex>;
} // namespace numbers
