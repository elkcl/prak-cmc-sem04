#include <cstdint>
#include <vector>

using std::vector;

void
process(vector<int64_t> &v, int64_t threshold)
{
    v.reserve(v.size() * 2);
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        if (*it >= threshold) {
            v.push_back(*it);
        }
    }
}
