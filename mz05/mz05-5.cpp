#include <cstdint>
#include <ios>
#include <iostream>
#include <map>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::map;
using std::pair;
using std::tuple;
using std::unordered_map;
using std::vector;

int
main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr uint32_t M = 4294967161;
    vector<tuple<uint32_t, uint32_t, uint64_t>> mat1;
    unordered_map<uint32_t, vector<pair<uint32_t, uint64_t>>> mat2; // row-major
    map<pair<uint32_t, uint32_t>, uint64_t> ans;
    uint32_t r, c;
    uint64_t v;
    bool fst_map = true;
    while (cin >> r) {
        cin >> c >> v;
        if (r == 0 && c == 0 && v == M) {
            fst_map = false;
            continue;
        }
        v %= M;
        if (v == 0) {
            continue;
        }
        if (fst_map) {
            mat1.emplace_back(r, c, v);
        } else {
            mat2[r].emplace_back(c, v);
        }
    }
    for (const auto &[r1, c1, v1] : mat1) {
        for (const auto &[c2, v2] : mat2[c1]) {
            ans[{r1, c2}] += v1 * v2;
            ans[{r1, c2}] %= M;
        }
    }
    for (const auto &[k3, v3] : ans) {
        if (v3 != 0) {
            cout << k3.first << ' ' << k3.second << ' ' << v3 << '\n';
        }
    }
}
