#pragma once
#include <string>
#include <vector>

namespace lab
{
    using Numbers = std::vector<int>;
    using Predicate = bool (*)(int);

    struct Experiment
    {
        const Numbers &values;
        std::string scenario;
        std::string predicate_name;
        Predicate predicate;
    };

    struct Timing
    {
        double milliseconds;
        bool result;
    };
}
