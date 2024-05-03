#include <cstdint>
#include <functional>
void
calc_binom(int m, int k, std::function<void(uint64_t)> cb)
{
    if (m == k) {
        cb(1);
    } else {
        calc_binom(m - 1, k, [m, k, cb](uint64_t x) -> void { cb(m * x / (m - k)); });
    }
}
