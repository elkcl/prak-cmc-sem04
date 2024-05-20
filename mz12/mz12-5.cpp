#include <iomanip>
#include <ios>
#include <iostream>
#include <mutex>
#include <thread>
#include <array>

constexpr size_t THR_CNT = 3;
constexpr size_t ITER_CNT = 1'000'000;

std::array<double, THR_CNT> a{};
std::mutex a_mutex;

void
thr_func(size_t thr)
{
    for (size_t i = 0; i < ITER_CNT; ++i) {
        const std::lock_guard lock{a_mutex};
        a[thr] += 100 * (thr + 1);
        a[(thr + 1) % 3] -= 100 * (thr + 1) + 1;
    }
}

int
main()
{
    std::array<std::thread, THR_CNT> thrs{};
    for (size_t thr = 0; thr < THR_CNT; ++thr) {
        thrs[thr] = std::thread(thr_func, thr);
    }
    for (size_t thr = 0; thr < THR_CNT; ++thr) {
        thrs[thr].join();
    }
    std::cout << std::fixed << std::setprecision(10);
    for (size_t thr = 0; thr < THR_CNT; ++thr) {
        std::cout << a[thr] << ' ';
    }
    std::cout << std::endl;
}
