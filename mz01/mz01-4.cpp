#include <iostream>
#include <cmath>
#include <iomanip>

using ld = long double;

int
main()
{
    constexpr int PRECISION = 10;
    ld sum = 0;
    ld sumsq = 0;
    int cnt = 0;
    ld curr = 0;
    while (std::cin >> curr) {
        ++cnt;
        sum += curr;
        sumsq += curr * curr;
    }
    ld mean = sum / cnt;
    ld mean_sq = sumsq / cnt;
    ld sigma = sqrt(mean_sq - mean * mean);
    std::cout << std::setprecision(PRECISION) << mean << ' ' << sigma << std::endl;
}
