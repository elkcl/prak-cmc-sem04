#include <algorithm>
#include <cstdint>
#include <sys/types.h>
#include <vector>

using std::vector;

void
process(const vector<uint64_t> &v1, vector<uint64_t> &v2, size_t step)
{
    auto it1 = v1.cbegin();
    auto it2 = v2.rbegin();
    for (; it1 < v1.cend() && it2 < v2.rend(); it1 += std::min(static_cast<ssize_t>(step), v1.cend() - it1), ++it2) {
        *it2 += *it1;
    }
}
