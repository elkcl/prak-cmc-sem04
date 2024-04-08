#include <cassert>
#include <cstdint>
#include <iostream>

struct Result
{
    int64_t res;
    bool valid;
};

// функция Аккермана, см.
// https://ru.wikipedia.org/wiki/%D0%A4%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F_%D0%90%D0%BA%D0%BA%D0%B5%D1%80%D0%BC%D0%B0%D0%BD%D0%B0
[[noreturn]] void
func(int64_t a, int64_t b, int32_t k)
{
    if (k < 0 || a < 1 || b < 1) {
        throw Result{0, false};
    }
    if (k == 0) {
        throw Result{a + b, true};
    }
    if (b == 1) {
        throw Result{a, true};
    }
    try {
        func(a, b - 1, k);
    } catch (const Result &f1) {
        if (!f1.valid) {
            throw;
        }
        func(a, f1.res, k - 1);
    }
}

int
main()
{
    int64_t a, b;
    int32_t k;
    while (std::cin >> a >> b >> k) {
        try {
            func(a, b, k);
        } catch (const Result &ans) {
            assert(ans.valid);
            std::cout << ans.res << std::endl;
        }
    }
}
