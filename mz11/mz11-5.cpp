#include <cctype>
#include <iostream>

enum class State
{
    S,
    A,
    B,
    BC,
    SF,
    F
};

int
main()
{
    auto s = State::S;
    char c;
    while (std::cin >> c) {
        if (std::isspace(c)) {
            continue;
        }
        switch (s) {
        case State::S:
            switch (c) {
            case 'a':
                s = State::A;
                break;
            case 'b':
                s = State::B;
                break;
            default:
                std::cout << "0\n";
                return 0;
            }
            break;
        case State::A:
            switch (c) {
            case 'a':
                s = State::S;
                break;
            case 'b':
                s = State::F;
                break;
            case 'c':
                s = State::BC;
                break;
            default:
                std::cout << "0\n";
                return 0;
            }
            break;
        case State::B:
            switch (c) {
            case 'a':
                s = State::S;
                break;
            default:
                std::cout << "0\n";
                return 0;
            }
            break;
        case State::BC:
            switch (c) {
            case 'a':
                s = State::SF;
                break;
            case 'b':
                s = State::B;
                break;
            default:
                std::cout << "0\n";
                return 0;
            }
            break;
        case State::SF:
            switch (c) {
            case 'a':
                s = State::A;
                break;
            case 'b':
                s = State::B;
                break;
            default:
                std::cout << "0\n";
                return 0;
            }
            break;
        case State::F:
            std::cout << "0\n";
            return 0;
            break;
        }
    }
    if (s == State::F || s == State::SF) {
        std::cout << "1\n";
    } else {
        std::cout << "0\n";
    }
}
