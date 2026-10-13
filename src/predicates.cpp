#include "predicates.h"

namespace lab::predicates
{
    bool positive(int value)
    {
        return value > 0;
    }

    bool prime(int value)
    {
        if (value < 2)
            return false;
        for (int divisor = 2; divisor <= value / divisor; ++divisor)
            if (value % divisor == 0)
                return false;
        return true;
    }
}
