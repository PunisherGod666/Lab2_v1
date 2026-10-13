#include "data.h"
#include <algorithm>
#include <fstream>
#include <random>

namespace lab::data
{
    using namespace std;
    const array<size_t, 3> sizes{1000, 100000, 1000000};
    const array<string, 3> cases{"all_true", "false_first", "false_last"};

    filesystem::path path(const filesystem::path &directory, size_t n,
                          const string &scenario)
    {
        return directory / (to_string(n) + "_" + scenario + ".txt");
    }

    void generate(const filesystem::path &directory)
    {
        filesystem::create_directories(directory);
        mt19937 engine(42);
        const array<int, 8> primes{1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049};
        uniform_int_distribution<int> choose(0, static_cast<int>(primes.size()) - 1);
        for (const auto n : sizes)
        {
            Numbers base(n);
            std::generate(base.begin(), base.end(), [&engine, &choose, &primes]
                          { return primes[choose(engine)]; });
            for (const auto &scenario : cases)
            {
                auto values = base;
                if (scenario == "false_first")
                    values.front() = -1;
                if (scenario == "false_last")
                    values.back() = -1;
                ofstream output(path(directory, n, scenario));
                output << n << '\n';
                for (const auto value : values)
                    output << value << ' ';
                output << '\n';
            }
        }
    }

    Numbers load(const filesystem::path &path)
    {
        ifstream input(path);
        size_t n = 0;
        input >> n;
        Numbers values(n);
        for (auto &value : values)
            input >> value;
        return values;
    }
}
