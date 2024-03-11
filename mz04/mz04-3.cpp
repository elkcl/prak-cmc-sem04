#include <algorithm>
#include <functional>
#include <vector>

using std::vector;

void
process(const vector<int> &v1, vector<int> &v2)
{
    vector<int> v1s(v1);
    std::sort(v1s.begin(), v1s.end(), std::greater<>());
    auto end = std::unique(v1s.begin(), v1s.end());
    for (auto it = v1s.begin(); it != end; ++it) {
        if (*it >= 0 && static_cast<size_t>(*it) < v2.size()) {
            v2.erase(v2.begin() + *it);
        }
    }
}
