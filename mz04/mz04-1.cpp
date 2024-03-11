#include <cstdint>
#include <vector>

using std::vector;

void
process(const vector<uint64_t> &v1, vector<uint64_t> &v2, size_t step)
{
    auto it1 = v1.cbegin();
    auto it2 = v2.rbegin();
    for (; it1 < v1.cend() && it2 < v2.rend(); it1 += step, ++it2) {
        *it2 += *it1;
    }
}
