#include <cctype>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Parser
{
private:
    char c{};

    bool
    gc()
    {
        bool ans;
        while ((ans = static_cast<bool>(cin >> c)) && std::isspace(c)) {
        }
        return ans;
    }
    bool
    eof()
    {
        return cin.eof();
    }

    void S();
    void A();
    void B();

public:
    bool
    parse()
    {
        gc();
        try {
            S();
        } catch (...) {
            return false;
        }
        return eof();
    }
};

void
Parser::S()
{
    if (eof()) {
        throw 0;
    }
    if (c == 'a') {
        gc();
        A();
        if (eof() || c != 'b') {
            throw 0;
        }
        gc();
    } else if (c == 'c') {
        gc();
        B();
    } else {
        throw 0;
    }
}

void
Parser::A()
{
    if (eof()) {
        throw 0;
    }
    if (c == 'c') {
        gc();
        A();
        if (eof() || c != 'd') {
            throw 0;
        }
        gc();
    } else if (c == 'e') {
        gc();
    } else {
        throw 0;
    }
}

void
Parser::B()
{
    if (eof()) {
        return;
    }
    if (c == 'b') {
        gc();
        B();
    } else if (c == 'd') {
        gc();
    } else {
        throw 0;
    }
}

int
main()
{
    Parser p;
    if (p.parse()) {
        cout << "1\n";
    } else {
        cout << "0\n";
    }
}
