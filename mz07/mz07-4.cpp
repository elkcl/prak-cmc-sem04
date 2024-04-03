// адаптировано с https://www.redblobgames.com/grids/hexagons/

#include <algorithm>
namespace Game
{
template <typename T> class Coord
{
public:
    T row, col;
    typedef T value_type;
    Coord(T row_ = 0, T col_ = 0) : row{row_}, col{col_} {}
};

template <typename T>
typename T::value_type
dist(const T &size, const T &p1, const T &p2)
{
    typedef typename T::value_type val_t;
    val_t q1 = p1.col;
    val_t q2 = p2.col;
    val_t r1 = p1.row - (p1.col + (p1.col & 1)) / 2;
    val_t r2 = p2.row - (p2.col + (p2.col & 1)) / 2;
    val_t s1 = -q1 - r1;
    val_t s2 = -q2 - r2;
    return std::max({std::abs(q1 - q2), std::abs(r1 - r2), std::abs(s1 - s2)});
}

} // namespace Game
