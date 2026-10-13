#include "policies.h"
#include "timing.h"
#include <execution>

namespace lab::policies
{
    using namespace std;

    template <class Policy>
    void benchmark_policy(const Experiment &test, Policy policy, const string &name)
    {
        timing::record(test, name, 0, [&test, policy]
                       { return all_of(policy, test.values.cbegin(), test.values.cend(), test.predicate); });
    }

    void run(const Experiment &test)
    {
        benchmark_policy(test, execution::seq, "seq");
        benchmark_policy(test, execution::unseq, "unseq");
        benchmark_policy(test, execution::par, "par");
        benchmark_policy(test, execution::par_unseq, "par_unseq");
    }
}
