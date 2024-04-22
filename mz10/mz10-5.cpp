#include <cctype>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

int
main()
{
    std::stack<std::string> st;
    char c;
    while (std::cin >> c) {
        if (std::isspace(c)) {
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            auto b = st.top();
            st.pop();
            auto a = st.top();
            st.pop();
            std::ostringstream ss;
            ss << '(' << a << c << b << ')';
            st.push(ss.str());
        } else {
            st.push(std::string(1, c));
        }
    }
    std::cout << st.top() << std::endl;
}
