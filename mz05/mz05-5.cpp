#include <cstdint>
#include <ios>
#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>

using std::cin;
using std::cout;
using std::map;
using std::pair;
using std::unordered_map;

int
main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr uint32_t M = 4294967161;
    unordered_map<uint32_t, unordered_map<uint32_t, uint64_t>> mat1;
    unordered_map<uint32_t, unordered_map<uint32_t, uint64_t>> mat2;
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
            mat1[r][c] = v;
        } else {
            mat2[c][r] = v;
        }
    }
    for (const auto &[r1, m1] : mat1) {
        for (const auto &[c2, m2] : mat2) {
            uint64_t res = 0;
            if (m1.size() <= m2.size()) {
                for (const auto &[c1, v1] : m1) {
                    if (auto it = m2.find(c1); it != m2.end()) {
                        res += (v1 * it->second) % M;
                    }
                }
            } else {
                for (const auto &[r2, v2] : m2) {
                    if (auto it = m1.find(r2); it != m1.end()) {
                        res += (v2 * it->second) % M;
                    }
                }
            }
            res %= M;
            if (res != 0) {
                ans[{r1, c2}] = res;
            }
        }
    }
    for (const auto &[k3, v3] : ans) {
        cout << k3.first << ' ' << k3.second << ' ' << v3 << '\n';
    }
}
