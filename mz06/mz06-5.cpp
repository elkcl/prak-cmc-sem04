#include <functional>
#include <utility>
template <typename T, typename C = std::less<>>
void
selection_sort(T it1, T it2, C cmp = std::less<>())
{
    T ans = it1;
    for (; ans != it2; ++ans) {
        T min = ans;
        for (T curr = ans; curr != it2; ++curr) {
            if (cmp(*curr, *min)) {
                min = curr;
            }
        }
        std::swap(*min, *ans);
    }
}
