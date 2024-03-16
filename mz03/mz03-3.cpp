#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
namespace numbers
{
complex_stack
binary_op(complex_stack st, const auto &op)
{
    auto z2 = +st;
    st = ~std::move(st);
    auto z1 = +st;
    return (~std::move(st)) << op(z1, z2);
}

complex_stack
unary_op(complex_stack st, const auto &op)
{
    auto z1 = +st;
    return (~std::move(st)) << op(z1);
}

std::unordered_map<char, std::function<complex_stack(complex_stack)>> ops{
    {'+', [](complex_stack st) -> complex_stack { return binary_op(std::move(st), std::plus<>()); }},
    {'-', [](complex_stack st) -> complex_stack { return binary_op(std::move(st), std::minus<>()); }},
    {'*', [](complex_stack st) -> complex_stack { return binary_op(std::move(st), std::multiplies<>()); }},
    {'/', [](complex_stack st) -> complex_stack { return binary_op(std::move(st), std::divides<>()); }},
    {'~', [](complex_stack st) -> complex_stack { return unary_op(std::move(st), std::bit_not<>()); }},
    {'#', [](complex_stack st) -> complex_stack { return unary_op(std::move(st), std::negate<>()); }},
    {'!',
     [](complex_stack st) -> complex_stack {
         auto z = +st;
         return std::move(st) << z;
     }},
    {';', [](complex_stack st) -> complex_stack { return ~std::move(st); }},
    {'z', [](complex_stack st) -> complex_stack {
         auto z = st[0];
         return std::move(st) << z;
     }}};

complex
eval(const std::vector<std::string> &args, const complex &z)
{
    complex_stack st;
    st = std::move(st) << z;
    for (const auto &op : args) {
        if (op.size() == 1) {
            st = ops[op[0]](std::move(st));
        } else {
            st = std::move(st) << complex{op};
        }
    }
    return +st;
}
} // namespace numbers
