#include <cstddef>
namespace Sample
{
template <typename T, size_t m, size_t n> class Matrix
{
private:
    T arr[m][n] = {};

public:
    T(&operator[](size_t i))[n]
    {
        return arr[i];
    }

    const T (&operator[](size_t i) const)[n]
    {
        return arr[i];
    }
};
} // namespace Sample
