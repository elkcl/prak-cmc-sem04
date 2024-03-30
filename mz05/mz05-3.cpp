#include <format>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

class Date
{
private:
    int y, m, d;

public:
    Date(int _y, int _m, int _d) : y{_y}, m{_m}, d{_d} {}
    friend std::ostream &operator<<(std::ostream &out, const Date &d);
    friend bool operator<(const Date &a, const Date &b);
};

std::ostream &
operator<<(std::ostream &out, const Date &d)
{
    out << std::format("{}/{:02}/{:02}", d.y, d.m, d.d);
    return out;
}

bool
operator<(const Date &a, const Date &b)
{
    if (a.y == b.y) {
        if (a.m == b.m) {
            return a.d < b.d;
        } else {
            return a.m < b.m;
        }
    } else {
        return a.y < b.y;
    }
}

int
main()
{
    std::set<Date> dates;
    std::set<std::string> names;
    std::map<std::pair<std::string_view, Date>, int> marks;
    std::string curr_name;
    while (std::cin >> curr_name) {
        int y, m, d, mark;
        char sep;
        std::cin >> y >> sep >> m >> sep >> d >> mark;
        Date date{y, m, d};
        auto [name_it, succ] = names.insert(curr_name);
        dates.insert(date);
        marks[{*name_it, date}] = mark;
    }
    std::cout << ". ";
    for (const auto &date : dates) {
        std::cout << date << ' ';
    }
    std::cout << std::endl;
    for (const auto &name : names) {
        std::cout << name << ' ';
        for (const auto &date : dates) {
            if (marks.contains({name, date})) {
                std::cout << marks[{name, date}] << ' ';
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}
