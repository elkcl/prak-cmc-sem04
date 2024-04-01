#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class FigureFactory
{
private:
    FigureFactory() {}
    FigureFactory(const FigureFactory &);
    void operator=(const FigureFactory &);

public:
    static FigureFactory &
    factory_instance()
    {
        static FigureFactory instance;
        return instance;
    }
    Figure *
    make(std::string st)
    {
        std::istringstream ss(st);
        char type;
        ss >> type;
        std::string params;
        std::getline(ss, params);
        if (type == 'R') {
            return Rectangle::make(params);
        } else if (type == 'S') {
            return Square::make(params);
        } else if (type == 'C') {
            return Circle::make(params);
        } else {
            return 0;
        }
    }
};

bool
fig_cmp(const Figure *a, const Figure *b)
{
    return a->get_square() < b->get_square();
}

int
main()
{
    std::vector<Figure *> figs;
    std::string ins;
    while (std::getline(std::cin, ins)) {
        figs.push_back(FigureFactory::factory_instance().make(ins));
    }
    std::stable_sort(figs.begin(), figs.end(), fig_cmp);
    for (size_t i = 0; i < figs.size(); ++i) {
        std::cout << figs[i]->to_string() << std::endl;
        delete figs[i];
    }
}
