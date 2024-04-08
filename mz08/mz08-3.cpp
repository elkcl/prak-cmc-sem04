#include <iostream>

class S
{
private:
    int a;
    bool print = true;

public:
    S()
    {
        std::cin >> a;
        if (!std::cin) {
            print = false;
        }
    }
    ~S()
    {
        if (print) {
            std::cout << a << std::endl;
        }
    }
    operator bool() { return !std::cin.eof(); }
    S(S &&s)
    {
        int b;
        std::cin >> b;
        if (!std::cin) {
            a = s.a;
        } else {
            a = s.a + b;
        }
        s.print = false;
    }
};
