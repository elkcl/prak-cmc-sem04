#include <iostream>
#include <string>

class RecString
{
private:
    std::string s;

public:
    RecString()
    {
        if (!(std::cin >> s)) {
            throw 1;
        }
    }
    ~RecString()
    {
        if (!s.empty()) {
            std::cout << s << std::endl;
        }
    }
};

[[noreturn]] void
f()
{
    RecString s;
    f();
}

int
main()
{
    try {
        f();
    } catch (...) {
    }
}
