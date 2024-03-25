#include <iterator>
template <typename T>
T::value_type
process(const T &cont)
{
    typename T::value_type ans{};
    auto it = std::rbegin(cont);
    if (it == std::rend(cont)) {
        return ans;
    }
    ans += *it;
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < 2 && it != std::rend(cont); ++i) {
            ++it;
        }
        if (it == std::rend(cont)) {
            return ans;
        }
        ans += *it;
    }
    return ans;
}
