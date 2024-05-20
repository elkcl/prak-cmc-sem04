#include <cstddef>
#include <cstdint>
#include <numeric>
#include <vector>

using std::vector;

void
process(vector<uint64_t> &v, uint32_t s)
{
    uint64_t sum = std::accumulate(v.begin(), v.end(), 0ll);
    size_t off = v.size() / s;
    v.resize(v.size() + off);
    for (size_t i = v.size() - 1; off > 0 && i >= off * (s + 1); --i) {
        v[i] = v[i - off];
        sum -= v[i];
    }
    for (size_t i = off * (s + 1) - 1; off > 0 && i != static_cast<size_t>(-1); --i) {
        if ((i + 1) % (s + 1) == 0) {
            v[i] = sum;
            off -= 1;
        } else {
            v[i] = v[i - off];
            sum -= v[i];
        }
    }
}
