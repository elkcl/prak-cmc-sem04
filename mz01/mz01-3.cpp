#include <iostream>

using std::cin;
using std::cout;

int
main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    bool print_zero = false;
    bool in_num = false;
    for (char curr = cin.get(); !cin.eof(); curr = cin.get()) {
        if (curr < '0' || curr > '9') {
            if (print_zero) {
                cout << '0';
                print_zero = false;
            }
            in_num = false;
            cout << curr;
        } else if (curr != '0') {
            print_zero = false;
            in_num = true;
            cout << curr;
        } else if (in_num) {
            cout << curr;
        } else {
            print_zero = true;
        }
    }
    if (print_zero) {
        cout << '0';
    }
}
