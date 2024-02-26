#include <string>

using std::string;

class BinaryNumber
{
  private:
    string str;

  public:
    BinaryNumber(const string &s) : str{s} {}
    operator string() const { return str; }
    const BinaryNumber &
    operator++()
    {
        size_t sz = str.size();
        bool carry = true;
        for (size_t i = sz - 1; i > 0; --i) {
            if (str[i] == '0') {
                str[i] = '1';
                carry = false;
                break;
            }
            str[i] = '0';
        }
        if (carry) {
            if (str[0] == '0') {
                str[0] = '1';
            } else {
                str[0] = '0';
                str.insert(0, 1, '1');
            }
        }
        return *this;
    }
};
