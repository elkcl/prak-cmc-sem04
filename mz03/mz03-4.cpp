#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::numbers::pi;

int
main(int argc, char **argv)
{
    numbers::complex c{argv[1]};
    double r = std::atof(argv[2]);
    int n = std::atoi(argv[3]);
    vector<string> args;
    for (int i = 4; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    numbers::complex ans = 0;
    numbers::complex curr{r, 0};
    const numbers::complex step{cos(2 * pi / n), sin(2 * pi / n)};
    for (int i = 0; i < n; ++i) {
        ans += numbers::eval(args, curr + c) * (curr * step - curr);
        curr *= step;
    }
    cout << ans.to_string() << endl;
}
