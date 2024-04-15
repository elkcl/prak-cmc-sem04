#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

bool
parse(const string &s)
{
    bool alpha = true;
    for (char c : s) {
        if (alpha && (c == '3' || c == '4')) {

        } else if (c == '1' || c == '2') {
            alpha = false;
        } else {
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
