// язык вида a^(n) 0^(m) b^(n) 1^(m)
// где n, m > 0
// язык типа 1 (контекстно-зависимый)
// S -> PQ
// P -> ab | aPb
// Q -> Z1 | ZQ1
// bZ -> Zb
// aZ -> a0
// 0Z -> 00

#include <iostream>
#include <string>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::strspn;

bool
parse(const string &s)
{
    if (s.empty()) {
        return false;
    }
    size_t n = strspn(s.c_str(), "a");
    if (n == 0) {
        return false;
    }
    size_t m = strspn(s.c_str() + n, "0");
    if (m == 0) {
        return false;
    }
    if (s.size() != 2 * (n + m)) {
        return false;
    }
    if (strspn(s.c_str() + n + m, "b") != n) {
        return false;
    }
    if (strspn(s.c_str() + n + m + n, "1") != m) {
        return false;
    }
    return true;
}

int
main()
{
    string s;
    while (cin >> s) {
        if (parse(s)) {
            cout << '1' << endl;
        } else {
            cout << '0' << endl;
        }
    }
}
