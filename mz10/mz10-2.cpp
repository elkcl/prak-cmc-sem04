#include <cctype>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <unordered_set>

int
main()
{
    std::unordered_map<char, std::vector<std::string>> gram;
    std::string l, r;
    while (std::cin >> l >> r) {
        gram[l[0]].push_back(r);
    }
    std::unordered_set<char> currT, currN, newN;
    currN.insert('S');
    newN.insert('S');
    bool changed = false;
    do {
        changed = false;
        for (char cN : currN) {
            for (const auto &s : gram[cN]) {
                if (s[0] == '_') {
                    continue;
                }
                for (char c : s) {
                    if (std::isupper(c)) {
                        auto [it, b] = newN.insert(c);
                        changed |= b;
                    } else {
                        auto [it, b] = currT.insert(c);
                        changed |= b;
                    }
                }
            }
        }
        currN = newN;
    } while (changed);
    for (const auto &[k, v] : gram) {
        if (!currN.contains(k)) {
            continue;
        }
        for (const auto &s : v) {
            if (s[0] == '_') {
                std::cout << k << " _" << std::endl;
            } else {
                bool valid = true;
                for (char c : s) {
                    if (!currN.contains(c) && !currT.contains(c)) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    std::cout << k << ' ' << s << std::endl;
                }
            }
        }
    }
}
