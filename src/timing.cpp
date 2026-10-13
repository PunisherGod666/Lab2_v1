#include "timing.h"
#include <format>
#include <iostream>
#include <thread>

namespace lab::timing
{
    using namespace std;
    volatile bool result_sink = false;

    void print_row(const Experiment &test, const string &method, unsigned k, Timing timing)
    {
        const unsigned hardware = max(1u, thread::hardware_concurrency());
        cout << format("{},{},{},{},{},{:.6f},{},{:.6f}\n", test.values.size(),
                       test.scenario, test.predicate_name, method, k,
                       timing.milliseconds, static_cast<int>(timing.result),
                       static_cast<double>(k) / hardware);
    }
}
