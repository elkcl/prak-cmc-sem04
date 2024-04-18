#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

int
main()
{
    bool containsS = false;
    bool noShort = true;
    bool contextFree = true;
    bool hasSeps = false;
    bool hasSright = false;
    std::string left, right;
    while (std::cin >> left >> right) {
        if (!std::any_of(left.begin(), left.end(), [](char x) { return std::isupper(x); })) {
            std::cout << "-1\n";
            return 0;
        }
        if (left.size() == 1 && left[0] == 'S') {
            containsS = true;
            if (right.size() == 1 && right[0] == '_') {
                hasSeps = true;
            }
        } else if (right.size() == 1 && right[0] == '_') {
            noShort = false;
        }
        if (left.size() > right.size()) {
            noShort = false;
        }
        if (left.size() != 1) {
            contextFree = false;
        }
        if (right.contains('S')) {
            hasSright = true;
        }
    }
    if (!containsS) {
        std::cout << "-1\n";
        return 0;
    }
    if (contextFree) {
        if (noShort && !(hasSeps && hasSright)) {
            std::cout << "23\n";
        } else {
            std::cout << "2\n";
        }
        return 0;
    }
    std::cout << "10\n";
}
