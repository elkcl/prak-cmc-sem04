#include <iostream>
#include <map>
#include <string>

struct Student
{
    int sum, cnt;
};

int
main()
{
    std::map<std::string, Student> db;
    std::string student;
    int mark;
    while (std::cin >> student) {
        std::cin >> mark;
        if (!db.contains(student)) {
            db[student] = {mark, 1};
        } else {
            db[student].sum += mark;
            ++db[student].cnt;
        }
    }
    for (const auto &[k, v] : db) {
        std::cout << k << ' ' << static_cast<double>(v.sum) / v.cnt << std::endl;
    }
}
