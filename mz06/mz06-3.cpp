#include <functional>
#include <iterator>
#include <vector>
template <typename T, typename F>
void
myapply(T it1, T it2, F &&f)
{
    for (; it1 != it2; ++it1) {
        f(*it1);
    }
}

template <typename T> using vec_t = std::vector<std::reference_wrapper<typename std::iterator_traits<T>::value_type>>;

template <typename T, typename F>
vec_t<T>
myfilter2(T it1, T it2, F &&f)
{
    vec_t<T> v{};
    for (; it1 != it2; ++it1) {
        if (f(*it1)) {
            v.push_back(std::ref(*it1));
        }
    }
    return v;
}
