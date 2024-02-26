#include <iostream>

using std::cin;
using std::cout;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << std::hex;

    char last = cin.get();
    int cnt = 1;
    if (cin.eof()) {
        return 0;
    }
    char curr = cin.get();
    while (!cin.eof()) {
        if (curr == last) {
            ++cnt;
        } else {
            if (last == '#' || cnt > 4) {
                cout << '#' << last << cnt << '#';
            } else {
                for (int i = 0; i < cnt; ++i) {
                    cout << last;
                }
            }
            last = curr;
            cnt = 1;
        }
        curr = cin.get();
    }
    if (last == '#' || cnt > 4) {
        cout << '#' << last << cnt << '#';
    } else {
        for (int i = 0; i < cnt; ++i) {
            cout << last;
        }
    }
}
