#include <iostream>

class A
{
  private:
    int num;
    bool print;

  public:
    A() : print{false} { std::cin >> num; }
    A(const A &a) : print{true}
    {
        std::cin >> num;
        num += a.num;
    }
    ~A()
    {
        if (print) {
            std::cout << num << std::endl;
        }
    }
};
