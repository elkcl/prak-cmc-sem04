#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int
main()
{
    std::vector<int> v;
    int a;
    while (std::cin >> a) {
        v.push_back(a);
    }
    std::stable_sort(v.begin(), v.end(), [](int a, int b) {
        return std::popcount(static_cast<unsigned>(a)) < std::popcount(static_cast<unsigned>(b));
    });
    for (int e : v) {
        std::cout << e << std::endl;
    }
}
