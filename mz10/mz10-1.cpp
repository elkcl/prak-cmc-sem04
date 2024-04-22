#include <algorithm>
#include <cctype>
#include <iostream>

int
main()
{
    bool noShort = true;
    bool leftReg = true;
    bool rightReg = true;
    bool hasSeps = false;
    bool hasSA = false;
    bool hasSright = false;
    bool autom = true;
    std::string left, right;
    while (std::cin >> left >> right) {
        if (left[0] == 'S') {
            if (right.size() == 1 && right[0] == '_') {
                hasSeps = true;
            }
        } else if (right.size() == 1 && right[0] == '_') {
            noShort = false;
            autom = false;
        }
        if (left.size() > right.size()) {
            noShort = false;
        }
        if (right.contains('S')) {
            hasSright = true;
        }
        size_t upcnt = std::count_if(right.begin(), right.end(), [](char x) { return std::isupper(x); });
        size_t lowcnt = std::count_if(right.begin(), right.end(), [](char x) { return std::islower(x); });
        if (upcnt > 1) {
            leftReg = rightReg = autom = false;
        }
        if (upcnt == 1 && lowcnt == 0) {
            if (hasSA) {
                autom = false;
            } else {
                hasSA = true;
            }
        }
        if (upcnt == 1 && lowcnt != 0 && std::isupper(right[0])) {
            rightReg = false;
        }
        if (upcnt == 1 && lowcnt != 0 && std::isupper(right.back())) {
            leftReg = false;
        }
        if (lowcnt > 1) {
            autom = false;
        }
    }
    if (hasSeps && hasSright) {
        noShort = false;
        autom = false;
    }
    if (hasSeps && !hasSA) {
        autom = false;
    }
    if (!hasSeps && hasSA) {
        autom = false;
    }
    if (autom && leftReg) {
        std::cout << 311 << std::endl;
    } else if (autom && rightReg) {
        std::cout << 321 << std::endl;
    } else if (leftReg) {
        std::cout << 31 << std::endl;
    } else if (rightReg) {
        std::cout << 32 << std::endl;
    } else if (noShort) {
        std::cout << 21 << std::endl;
    } else {
        std::cout << 2 << std::endl;
    }
}
