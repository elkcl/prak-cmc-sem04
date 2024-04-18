// S -> aXd
// X -> aXd | bP
// P -> bPc | c

#include <iostream>

void S(int n, int m);
void X(int n, int m);
void P(int n, int m);

void
S(int n, int m)
{
    std::cout << 'a';
    X(n - 1, m);
    std::cout << 'd';
}

void
X(int n, int m)
{
    if (n > 0) {
        std::cout << 'a';
        X(n - 1, m);
        std::cout << 'd';
    } else {
        std::cout << 'b';
        P(n, m - 1);
    }
}

void
P(int n, int m)
{
    if (m > 0) {
        std::cout << 'b';
        P(n, m - 1);
        std::cout << 'c';
    } else {
        std::cout << 'c';
    }
}

void
print(int n, int m)
{
    if (n == 0) {
        return;
    }
    S(n, m);
    std::cout << std::endl;
    print(n - 1, m + 1);
}

int
main()
{
    int k;
    std::cin >> k;
    if (k % 2 == 0) {
        print(k / 2 - 1, 1);
    }
}
