#include <iostream>
#include <chrono>

using ymd_t = std::chrono::year_month_day;
using std::chrono::day;
using std::chrono::days;
using std::chrono::duration_cast;
using std::chrono::month;
using std::chrono::sys_days;
using std::chrono::year;

int
main()
{
    int y, m, d;
    char hyp;
    std::cin >> y >> hyp >> m >> hyp >> d;
    ymd_t last = year(y) / month(m) / day(d);
    int64_t ans = 0;
    while (std::cin >> y >> hyp >> m >> hyp >> d) {
        ymd_t curr = year(y) / month(m) / day(d);
        decltype(sys_days(last) - sys_days(curr)) diff;
        if (last > curr) {
            diff = sys_days(last) - sys_days(curr);
        } else {
            diff = sys_days(curr) - sys_days(last);
        }
        ans += duration_cast<days>(diff).count();
        last = curr;
    }
    std::cout << ans << std::endl;
}
