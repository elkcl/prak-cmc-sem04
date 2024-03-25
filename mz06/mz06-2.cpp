#include <iterator>
template <typename T, typename F>
T
myfilter(const T &cont, F &&f)
{
    T ans{};
    for (const auto &el : cont) {
        if (f(el)) {
            ans.insert(std::end(ans), el);
        }
    }
    return ans;
}
