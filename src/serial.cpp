#include "serial.h"
#include "timing.h"

namespace lab::serial
{
    using namespace std;

    void run(const Experiment &test)
    {
        timing::record(test, "no_policy", 0, [&test]
                       { return all_of(test.values.cbegin(), test.values.cend(), test.predicate); });
    }
}
