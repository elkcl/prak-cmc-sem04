#include <algorithm>
#include <iomanip>
#include <ios>
#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

void
drop10(vector<double> &v)
{
    constexpr size_t DROP_PART = 10;
    size_t cnt = v.size() / DROP_PART;
    v.erase(v.begin(), v.begin() + cnt);
    v.erase(v.end() - cnt, v.end());
}

class SumFunctor
{
private:
    double m_sum = 0;

public:
    double
    sum() const
    {
        return m_sum;
    }
    void
    operator()(double x)
    {
        m_sum += x;
    }
};

int
main()
{
    constexpr int PRECISION = 10;
    vector<double> v;
    double in;
    while (cin >> in) {
        v.push_back(in);
    }
    drop10(v);
    std::sort(v.begin(), v.end());
    drop10(v);
    auto func = std::for_each(v.begin(), v.end(), SumFunctor());
    cout << std::fixed << std::setprecision(PRECISION);
    cout << func.sum() / v.size() << endl;
}
