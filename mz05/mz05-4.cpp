#include <cstdint>
#include <iostream>
#include <map>
#include <utility>

using std::cin;
using std::cout;
using std::endl;

int
main()
{
    constexpr uint32_t M = 4294967161;
    std::map<std::pair<uint32_t, uint32_t>, uint64_t> mat;
    uint32_t r, c;
    uint64_t v;
    while (cin >> r) {
        cin >> c >> v;
        if (r == 0 && c == 0 && v == M) {
            continue;
        }
        auto [it, ins] = mat.insert({{r, c}, v % M});
        if (!ins) {
            it->second += v;
            it->second %= M;
        }
        if (it->second == 0) {
            mat.erase(it);
        }
    }
    for (const auto &[key, val] : mat) {
        cout << key.first << ' ' << key.second << ' ' << val << endl;
    }
}
