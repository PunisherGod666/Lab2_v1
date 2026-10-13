#include "app.h"
#include "data.h"
#include "predicates.h"
#include "timing.h"
#include <format>
#include <iostream>
#include <thread>

namespace lab::app
{
    using namespace std;

    void print_header(int version)
    {
#ifdef _MSC_VER
        const string compiler = format("MSVC={}", _MSC_FULL_VER);
#else
        const string compiler = "compiler=" __VERSION__;
#endif
        cout << format("# all_of; version={}; {}; C++20; Release; optimization={}\n",
                       version, compiler, OPTIMIZATION_LEVEL);
        cout << format("# hardware_threads={}; repetitions={}; statistic=median; warm_up=1\n",
                       thread::hardware_concurrency(), timing::repetitions);
        cout << "N,case,predicate,method,K,median_ms,result,K_over_H\n";
    }

    int run(int argc, char *argv[], int version, const Part parts[], size_t count)
    {
        if (argc == 3 && string(argv[1]) == "--generate")
        {
            data::generate(argv[2]);
            cout << "Generated 9 input files with seed 42.\n";
            return 0;
        }
        const filesystem::path directory = argc > 1 ? argv[1] : "data";
        print_header(version);
        const pair<string, Predicate> predicates[]{
            {"positive", predicates::positive}, {"prime", predicates::prime}};
        for (const auto n : data::sizes)
        {
            for (const auto &scenario : data::cases)
            {
                const auto values = data::load(data::path(directory, n, scenario));
                for (const auto &[name, predicate] : predicates)
                {
                    const Experiment test{values, scenario, name, predicate};
                    for (size_t i = 0; i < count; ++i)
                        parts[i](test);
                }
            }
        }
        return 0;
    }
}
