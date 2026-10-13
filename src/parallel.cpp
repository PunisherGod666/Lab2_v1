#include "parallel.h"
#include "timing.h"
#include <limits>
#include <set>

namespace lab::parallel
{
    using namespace std;

    set<unsigned> thread_counts(size_t n)
    {
        const unsigned hardware = max(1u, thread::hardware_concurrency());
        set<unsigned> counts{1, 2, 3, hardware, 2 * hardware, 4 * hardware};
        for (unsigned k = 4; k <= 4 * hardware; k *= 2)
            counts.insert(k);
        erase_if(counts, [n](unsigned k)
                 { return k > n; });
        return counts;
    }

    void run(const Experiment &test)
    {
        Timing best{numeric_limits<double>::infinity(), false};
        unsigned best_k = 1;
        for (const auto k : thread_counts(test.values.size()))
        {
            const auto result = timing::record(test, "custom", k, [&test, k]
                                              { return parallel_all_of(test.values.cbegin(), test.values.cend(), test.predicate, k); });
            if (result.milliseconds < best.milliseconds)
            {
                best = result;
                best_k = k;
            }
        }
        timing::print_row(test, "best_K", best_k, best);
    }
}
