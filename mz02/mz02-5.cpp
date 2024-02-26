#include <array>

class Matrix
{
  private:
    using buf_t = std::array<std::array<int, 3>, 3>;
    buf_t buf{};

  public:
    int &
    operator[](int a, int b)
    {
        return buf[a][b];
    }
    using iterator = buf_t::iterator;
    using const_iterator = buf_t::const_iterator;
    iterator
    begin()
    {
        return buf.begin();
    }
    const_iterator
    begin() const
    {
        return buf.begin();
    }
    const_iterator
    cbegin() const
    {
        return buf.cbegin();
    }
    iterator
    end()
    {
        return buf.end();
    }
    const_iterator
    end() const
    {
        return buf.end();
    }
    const_iterator
    cend() const
    {
        return buf.cend();
    }
};
