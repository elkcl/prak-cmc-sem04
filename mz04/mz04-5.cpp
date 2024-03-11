#include <list>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::list;

int
main()
{
    list<int> l;
    int in;
    while (cin >> in && in != 0) {
        l.push_back(in);
    }
    int x, y;
    while (cin >> x) {
        if (x > 0) {
            cin >> y;
            --x;
            auto it = l.begin();
            while (it != l.end() && x--) {
                ++it;
            }
            l.insert(it, y);
        } else {
            x *= -1;
            --x;
            if (static_cast<size_t>(x) >= l.size()) {
                continue;
            }
            auto it = l.begin();
            while (x--) {
                ++it;
            }
            l.erase(it);
        }
    }
    for (auto el : l) {
        cout << el << endl;
    }
}
