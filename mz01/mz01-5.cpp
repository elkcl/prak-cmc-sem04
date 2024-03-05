#include <iostream>
#include <ios>
#include <cstdint>

using std::cin;
using std::cout;
using std::endl;

int
main()
{
    constexpr int OCTET_SIZE = 8;
    constexpr int OCTET_CNT = 4;
    cin >> std::hex;
    uint32_t num = 0;
    uint32_t curr = 0;
    uint32_t off = 0;
    bool reached_eof = false;
    while (!reached_eof && cin >> off) {
        for (int i = 0; i < OCTET_CNT; ++i) {
            for (int j = (OCTET_CNT - 1) * OCTET_SIZE; j >= 0; j -= OCTET_SIZE) {
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
