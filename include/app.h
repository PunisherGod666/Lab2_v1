#pragma once
#include "common.h"
#include <cstddef>

namespace lab::app
{
    using Part = void (*)(const Experiment &);
    int run(int argc, char *argv[], int version, const Part parts[], std::size_t count);
}
