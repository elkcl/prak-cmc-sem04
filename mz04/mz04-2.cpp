#include <cstdint>
#include <vector>

using std::vector;

void
process(vector<int64_t> &v, int64_t threshold)
{
    size_t ext = 0;
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        if (*it >= threshold) {
            ++ext;
        }
    }
    v.reserve(v.size() + ext);
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        if (*it >= threshold) {
            v.push_back(*it);
        }
    }
}
