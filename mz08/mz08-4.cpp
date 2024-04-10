#include <array>
#include <complex>
#include <limits>
#include <utility>
#include <vector>
namespace Equations
{

template <typename T>
bool
zero(const std::complex<T> &c)
{
    return std::norm(c) < 32 * std::numeric_limits<T>::epsilon();
}

template <typename T>
std::pair<bool, std::vector<std::complex<T>>>
quadratic(const std::array<std::complex<T>, 3> &v)
{
    if (zero(v[2])) {
        if (zero(v[1])) {
            if (zero(v[0])) {
                return {false, {}};
            } else {
                return {true, {}};
            }
        } else {
            return {true, {-v[0] / v[1]}};
        }
    } else {
        auto droot = std::sqrt(v[1] * v[1] - std::complex<T>(4.0) * v[0] * v[2]);
        return {true, {(-v[1] + droot) / (std::complex<T>(2.0) * v[2]), (-v[1] - droot) / (std::complex<T>(2.0) * v[2])}};
    }
}
} // namespace Equations
