#include <cstdint>
#include <string>

std::string
gen_power(uint32_t power)
{
    if (power == 0) {
        return "1";
    }
    if (power == 1) {
        return "x";
    }
    if (power % 2 == 0) {
        return gen_power(power / 2) + "!*";
    } else {
        return gen_power(power / 2) + "!*x*";
    }
}
