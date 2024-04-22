#include <iostream>
#include <map>
#include <string>
#include <unordered_set>
#include <utility>

int
main()
{
    std::map<std::pair<std::string, char>, std::string> tr;
    std::string curS, ch, newS;
    std::cin >> curS;
    while (curS != "END") {
        std::cin >> ch >> newS;
        tr[{curS, ch[0]}] = newS;
        std::cin >> curS;
    }
    std::unordered_set<std::string> termS;
    std::cin >> curS;
    while (curS != "END") {
        termS.insert(curS);
        std::cin >> curS;
    }
    std::string startS, input;
    std::cin >> startS >> input;
    size_t i = 0;
    for (; i < input.size(); ++i) {
        if (!tr.contains({startS, input[i]})) {
            std::cout << '0' << std::endl;
            std::cout << i << std::endl;
            std::cout << startS << std::endl;
            return 0;
        }
        startS = tr[{startS, input[i]}];
    }
    if (termS.contains(startS)) {
        std::cout << '1' << std::endl;
    } else {
        std::cout << '0' << std::endl;
    }
    std::cout << i << std::endl;
    std::cout << startS << std::endl;
}
