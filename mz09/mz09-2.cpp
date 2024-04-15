#include <iostream>
#include <string>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::string;

bool
parse(const string &s)
{
    if (s.empty()) {
        return false;
    }
    size_t k = std::strspn(s.c_str(), "0");
    if (k == 0) {
        return false;
    }
    size_t m = std::strspn(s.c_str() + k, "1");
    if (m == 0) {
        return false;
    }
    if (s.size() % (k + m) != 0) {
        return false;
    }
    for (size_t i = k + m; i < s.size(); i += k + m) {
        if (std::strspn(s.c_str() + i, "0") != k) {
            return false;
        }
        if (std::strspn(s.c_str() + i + k, "1") != m) {
            return false;
        }
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
