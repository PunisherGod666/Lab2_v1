// Compiler: MSVC 19.51, C++20.
#include "app.h"
#include "serial.h"
#include "policies.h"
#include "parallel.h"
#include <iterator>

int main(int argc, char *argv[])
{
    const lab::app::Part parts[]{lab::serial::run, lab::policies::run, lab::parallel::run};
    return lab::app::run(argc, argv, 1, parts, std::size(parts));
}
