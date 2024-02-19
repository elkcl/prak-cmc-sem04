#include <iostream>
#include <ios>
#include <cstdint>

using std::cin;
using std::cout;
using std::endl;

int
main()
{
    cin >> std::hex;
    uint32_t num = 0;
    uint32_t curr = 0;
    uint32_t off = 0;
    bool reached_eof = false;
    while (!reached_eof && cin >> off) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 3 * 8; j >= 0; j -= 8) {
                cin >> curr;
                if (cin.eof()) {
                    reached_eof = true;
                    break;
                }
                num |= curr << j;
            }
            if (reached_eof) {
                break;
            }
            cout << num << endl;
            num = 0;
        }
    }
}
