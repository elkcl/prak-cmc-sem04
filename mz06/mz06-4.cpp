#include <iterator>
#include <set>
#include <utility>
template <typename I, typename T>
T
myremove(I ind1, I ind2, T it1, T it2)
{
    std::set s(ind1, ind2);
    auto ans = it1;
    typename std::iterator_traits<I>::value_type curr{};
    for (; it1 != it2; ++it1, ++curr) {
        if (!s.contains(curr)) {
            std::swap(*ans, *it1);
            ++ans;
        }
    }
    return ans;
}
