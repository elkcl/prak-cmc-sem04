#include <cstdint>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

struct ThreadInfo
{
    uint32_t cnt;
    uint32_t acc1;
    double inc1;
    uint32_t acc2;
    double inc2;
};

void
thr_func(ThreadInfo thr, std::vector<double> &a, std::vector<std::mutex> &a_mutex)
{
    for (uint32_t i = 0; i < thr.cnt; ++i) {
        const std::scoped_lock lock{a_mutex[thr.acc1], a_mutex[thr.acc2]};
        a[thr.acc1] += thr.inc1;
        a[thr.acc2] += thr.inc2;
    }
}

int
main()
{
    uint32_t acc_cnt, thr_cnt;
    std::cin >> acc_cnt >> thr_cnt;
    std::vector<double> a(acc_cnt, 0);
    std::vector<std::mutex> a_mutex(acc_cnt);
    std::vector<std::thread> thrs(thr_cnt);
    for (uint32_t i = 0; i < thr_cnt; ++i) {
        ThreadInfo info;
        std::cin >> info.cnt >> info.acc1 >> info.inc1 >> info.acc2 >> info.inc2;
        thrs[i] = std::thread(thr_func, info, std::ref(a), std::ref(a_mutex));
    }
    for (uint32_t i = 0; i < thr_cnt; ++i) {
        thrs[i].join();
    }
    std::cout << std::fixed << std::setprecision(10);
    for (uint32_t i = 0; i < acc_cnt; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
}
